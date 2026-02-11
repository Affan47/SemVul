computeBlockDisposition(const SCEV *S, const BasicBlock *BB) {
  switch (S->getSCEVType()) {
  case scConstant:
    return ProperlyDominatesBlock;
  case scTruncate:
  case scZeroExtend:
  case scSignExtend:
    return getBlockDisposition(cast<SCEVCastExpr>(S)->getOperand(), BB);
  case scAddRecExpr: {


    const SCEVAddRecExpr *AR = cast<SCEVAddRecExpr>(S);
    if (!DT->dominates(AR->getLoop()->getHeader(), BB))
      return DoesNotDominateBlock;
  }

  case scAddExpr:
  case scMulExpr:
  case scUMaxExpr:
  case scSMaxExpr: {
    const SCEVNAryExpr *NAry = cast<SCEVNAryExpr>(S);
    bool Proper = true;
    for (SCEVNAryExpr::op_iterator I = NAry->op_begin(), E = NAry->op_end();
         I != E; ++I) {
      BlockDisposition D = getBlockDisposition(*I, BB);
      if (D == DoesNotDominateBlock)
        return DoesNotDominateBlock;
      if (D == DominatesBlock)
        Proper = false;
    }
    return Proper ? ProperlyDominatesBlock : DominatesBlock;
  }
  case scUDivExpr: {
    const SCEVUDivExpr *UDiv = cast<SCEVUDivExpr>(S);
    const SCEV *LHS = UDiv->getLHS(), *RHS = UDiv->getRHS();
    BlockDisposition LD = getBlockDisposition(LHS, BB);
    if (LD == DoesNotDominateBlock)
      return DoesNotDominateBlock;
    BlockDisposition RD = getBlockDisposition(RHS, BB);
    if (RD == DoesNotDominateBlock)
      return DoesNotDominateBlock;
    return (LD == ProperlyDominatesBlock && RD == ProperlyDominatesBlock) ?
      ProperlyDominatesBlock : DominatesBlock;
  }
  case scUnknown:
    if (Instruction *I =
          dyn_cast<Instruction>(cast<SCEVUnknown>(S)->getValue())) {
      if (I->getParent() == BB)
        return DominatesBlock;
      if (DT->properlyDominates(I->getParent(), BB))
        return ProperlyDominatesBlock;
      return DoesNotDominateBlock;
    }
    return ProperlyDominatesBlock;
  case scCouldNotCompute:
    llvm_unreachable("Attempt to use a SCEVCouldNotCompute object!");
    return DoesNotDominateBlock;
  default: break;
  }
  llvm_unreachable("Unknown SCEV kind!");
  return DoesNotDominateBlock;
}
