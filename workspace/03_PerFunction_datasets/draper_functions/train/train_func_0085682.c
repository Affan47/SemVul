replaceAndRecursivelySimplifyImpl(Instruction *I, Value *SimpleV,
                                              const TargetLibraryInfo *TLI,
                                              const DominatorTree *DT,
                                              AssumptionCache *AC) {
  bool Simplified = false;
  SmallSetVector<Instruction *, 8> Worklist;
  const DataLayout &DL = I->getModule()->getDataLayout();


  if (SimpleV) {
    for (User *U : I->users())
      if (U != I)
        Worklist.insert(cast<Instruction>(U));


    I->replaceAllUsesWith(SimpleV);


    if (I->getParent())
      I->eraseFromParent();
  } else {
    Worklist.insert(I);
  }


  for (unsigned Idx = 0; Idx != Worklist.size(); ++Idx) {
    I = Worklist[Idx];


    SimpleV = SimplifyInstruction(I, DL, TLI, DT, AC);
    if (!SimpleV)
      continue;

    Simplified = true;


    for (User *U : I->users())
      Worklist.insert(cast<Instruction>(U));


    I->replaceAllUsesWith(SimpleV);


    if (I->getParent())
      I->eraseFromParent();
  }
  return Simplified;
}
