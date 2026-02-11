InjectCoverageAtBlock(Function &F, BasicBlock &BB,
                                                    bool UseCalls) {


  if (isa<UnreachableInst>(BB.getTerminator()))
    return;
  BasicBlock::iterator IP = BB.getFirstInsertionPt();

  bool IsEntryBB = &BB == &F.getEntryBlock();
  DebugLoc EntryLoc;
  if (IsEntryBB) {
    if (auto SP = getDISubprogram(&F))
      EntryLoc = DebugLoc::get(SP->getScopeLine(), 0, SP);


    IP = PrepareToSplitEntryBlock(BB, IP);
  } else {
    EntryLoc = IP->getDebugLoc();
  }

  IRBuilder<> IRB(&*IP);
  IRB.SetCurrentDebugLocation(EntryLoc);
  Value *GuardP = IRB.CreateAdd(
      IRB.CreatePointerCast(GuardArray, IntptrTy),
      ConstantInt::get(IntptrTy, (1 + NumberOfInstrumentedBlocks()) * 4));
  Type *Int32PtrTy = PointerType::getUnqual(IRB.getInt32Ty());
  GuardP = IRB.CreateIntToPtr(GuardP, Int32PtrTy);
  if (UseCalls) {
    IRB.CreateCall(SanCovWithCheckFunction, GuardP);
  } else {
    LoadInst *Load = IRB.CreateLoad(GuardP);
    Load->setAtomic(Monotonic);
    Load->setAlignment(4);
    SetNoSanitizeMetadata(Load);
    Value *Cmp = IRB.CreateICmpSGE(Constant::getNullValue(Load->getType()), Load);
    Instruction *Ins = SplitBlockAndInsertIfThen(
        Cmp, &*IP, false, MDBuilder(*C).createBranchWeights(1, 100000));
    IRB.SetInsertPoint(Ins);
    IRB.SetCurrentDebugLocation(EntryLoc);

    IRB.CreateCall(SanCovFunction, GuardP);
    IRB.CreateCall(EmptyAsm, {});
  }

  if (Options.Use8bitCounters) {
    IRB.SetInsertPoint(&*IP);
    Value *P = IRB.CreateAdd(
        IRB.CreatePointerCast(EightBitCounterArray, IntptrTy),
        ConstantInt::get(IntptrTy, NumberOfInstrumentedBlocks() - 1));
    P = IRB.CreateIntToPtr(P, IRB.getInt8PtrTy());
    LoadInst *LI = IRB.CreateLoad(P);
    Value *Inc = IRB.CreateAdd(LI, ConstantInt::get(IRB.getInt8Ty(), 1));
    StoreInst *SI = IRB.CreateStore(Inc, P);
    SetNoSanitizeMetadata(LI);
    SetNoSanitizeMetadata(SI);
  }

  if (Options.TraceBB) {


    IRB.SetInsertPoint(&*IP);
    IRB.CreateCall(IsEntryBB ? SanCovTraceEnter : SanCovTraceBB, GuardP);
  }
}
