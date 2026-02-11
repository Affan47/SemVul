RateRegister(const SCEV *Reg,
                        SmallPtrSet<const SCEV *, 16> &Regs,
                        const Loop *L,
                        ScalarEvolution &SE, DominatorTree &DT) {
  if (const SCEVAddRecExpr *AR = dyn_cast<SCEVAddRecExpr>(Reg)) {
    if (AR->getLoop() == L)
      AddRecCost += 1;


    else if (L->contains(AR->getLoop()) ||
             (!AR->getLoop()->contains(L) &&
              DT.dominates(L->getHeader(), AR->getLoop()->getHeader()))) {
      for (BasicBlock::iterator I = AR->getLoop()->getHeader()->begin();
           PHINode *PN = dyn_cast<PHINode>(I); ++I)
        if (SE.isSCEVable(PN->getType()) &&
            (SE.getEffectiveSCEVType(PN->getType()) ==
             SE.getEffectiveSCEVType(AR->getType())) &&
            SE.getSCEV(PN) == AR)
          return;


      ++NumBaseAdds;
      if (!Regs.count(AR->getStart()))
        RateRegister(AR->getStart(), Regs, L, SE, DT);
    }


    if (!AR->isAffine() || !isa<SCEVConstant>(AR->getOperand(1)))
      if (!Regs.count(AR->getStart()))
        RateRegister(AR->getOperand(1), Regs, L, SE, DT);
  }
  ++NumRegs;


  if (!isa<SCEVUnknown>(Reg) &&
      !isa<SCEVConstant>(Reg) &&
      !(isa<SCEVAddRecExpr>(Reg) &&
        (isa<SCEVUnknown>(cast<SCEVAddRecExpr>(Reg)->getStart()) ||
         isa<SCEVConstant>(cast<SCEVAddRecExpr>(Reg)->getStart()))))
    ++SetupCost;
}
