/*
 * Copyright (c) 1996-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#if !defined (_R_E_INSTRUMENTATION_H_)
#define _R_E_INSTRUMENTATION_H_

#include "r_e_Base.h"

namespace Dyninst {
namespace Relocation {

class Inst : public Element {
 public:
  typedef dyn_detail::boost::shared_ptr<Inst> Ptr;

  // I believe I can patch in the current code generation
  // system here...
  static Ptr create();

  Inst() {};

  // This sucks. It seriously sucks. But hey...
  // this points to all the baseTramps with instrumentation
  // at this point. This can be 0, 1, or 2 - 2 if we have
  // post instruction + pre instruction instrumentation.

  void addBaseTramp(baseTramp *b);
  bool empty() const;

  bool generate(Block &, GenStack &);
  
  virtual ~Inst() {};

  virtual std::string format() const;

 private:

  std::list<baseTramp *> baseTramps_;

};

struct InstPatch : public Patch {
  InstPatch(baseTrampInstance *a) : base(a) {};
  
  virtual bool apply(codeGen &gen, int iteration, int shift);
  virtual bool preapply(codeGen &gen);
  virtual ~InstPatch();

  baseTrampInstance *base;
};



};
};
#endif
