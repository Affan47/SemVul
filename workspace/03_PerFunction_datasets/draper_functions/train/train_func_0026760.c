HandleCallsInBlockInlinedThroughInvoke(BasicBlock *BB,
                                                   InvokeInliningInfo &Invoke) {
  LandingPadInst *LPI = Invoke.getLandingPadInst();

  for (BasicBlock::iterator BBI = BB->begin(), E = BB->end(); BBI != E; ) {
    Instruction *I = BBI++;

    if (LPI)
      if (LandingPadInst *L = dyn_cast<LandingPadInst>(I)) {
        unsigned NumClauses = LPI->getNumClauses();
        L->reserveClauses(NumClauses);
        for (unsigned i = 0; i != NumClauses; ++i)
          L->addClause(LPI->getClause(i));
      }


    CallInst *CI = dyn_cast<CallInst>(I);
    if (CI == 0) continue;


    if (EHSelectorInst *Inner = dyn_cast<EHSelectorInst>(CI)) {
      EHSelectorInst *Outer = Invoke.getOuterSelector();
      if (!Outer) continue;

      bool innerIsOnlyCleanup = isCleanupOnlySelector(Inner);
      bool outerIsOnlyCleanup = isCleanupOnlySelector(Outer);


      if (innerIsOnlyCleanup && outerIsOnlyCleanup) continue;


      SmallVector<Value*, 16> NewSelector;
      for (unsigned i = 0, e = Inner->getNumArgOperands(); i != e; ++i)
        NewSelector.push_back(Inner->getArgOperand(i));
      for (unsigned i = 2, e = Outer->getNumArgOperands(); i != e; ++i)
        NewSelector.push_back(Outer->getArgOperand(i));

      CallInst *NewInner =
        IRBuilder<>(Inner).CreateCall(Inner->getCalledValue(), NewSelector);

      NewInner->takeName(Inner);
      Inner->replaceAllUsesWith(NewInner);
      Inner->eraseFromParent();
      continue;
    }


    if (CI->doesNotThrow())
      continue;


    BasicBlock *Split = BB->splitBasicBlock(CI, CI->getName()+".noexc");


    BB->getInstList().pop_back();


    if (Invoke.forwardEHResume(CI, BB)) {


      return true;
    }


    ImmutableCallSite CS(CI);
    SmallVector<Value*, 8> InvokeArgs(CS.arg_begin(), CS.arg_end());
    InvokeInst *II =
      InvokeInst::Create(CI->getCalledValue(), Split,
                         Invoke.getOuterUnwindDest(),
                         InvokeArgs, CI->getName(), BB);
    II->setCallingConv(CI->getCallingConv());
    II->setAttributes(CI->getAttributes());


    CI->replaceAllUsesWith(II);

    Split->getInstList().pop_front();


    Invoke.addIncomingPHIValuesFor(BB);
    return false;
  }

  return false;
}
