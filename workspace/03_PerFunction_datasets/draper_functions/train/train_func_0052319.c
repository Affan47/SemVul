reuseOrInsertFastDiv(Function &F,
                                 Function::iterator &I,
                                 BasicBlock::iterator &J,
                                 IntegerType *BypassType,
                                 bool UseDivOp,
                                 bool UseSignedOp,
                                 DivCacheTy &PerBBDivCache) {

  Instruction *Instr = &*J;
  DivOpInfo Key(UseSignedOp, Instr->getOperand(0), Instr->getOperand(1));
  DivCacheTy::iterator CacheI = PerBBDivCache.find(Key);

  if (CacheI == PerBBDivCache.end()) {

    return insertFastDiv(F, I, J, BypassType, UseDivOp, UseSignedOp,
                         PerBBDivCache);
  }


  DivPhiNodes &Value = CacheI->second;
  if (UseDivOp) {

    J->replaceAllUsesWith(Value.Quotient);
  } else {

    J->replaceAllUsesWith(Value.Remainder);
  }


  ++J;


  Instr->eraseFromParent();
  return true;
}
