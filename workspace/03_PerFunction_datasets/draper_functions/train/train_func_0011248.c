chooseInstructionsToInstrument(
    SmallVectorImpl<Instruction *> &Local, SmallVectorImpl<Instruction *> &All,
    const DataLayout &DL) {
  SmallSet<Value*, 8> WriteTargets;

  for (SmallVectorImpl<Instruction*>::reverse_iterator It = Local.rbegin(),
       E = Local.rend(); It != E; ++It) {
    Instruction *I = *It;
    if (StoreInst *Store = dyn_cast<StoreInst>(I)) {
      WriteTargets.insert(Store->getPointerOperand());
    } else {
      LoadInst *Load = cast<LoadInst>(I);
      Value *Addr = Load->getPointerOperand();
      if (WriteTargets.count(Addr)) {

        NumOmittedReadsBeforeWrite++;
        continue;
      }
      if (addrPointsToConstantData(Addr)) {

        continue;
      }
    }
    Value *Addr = isa<StoreInst>(*I)
        ? cast<StoreInst>(I)->getPointerOperand()
        : cast<LoadInst>(I)->getPointerOperand();
    if (isa<AllocaInst>(GetUnderlyingObject(Addr, DL)) &&
        !PointerMayBeCaptured(Addr, true, true)) {


      NumOmittedNonCaptured++;
      continue;
    }
    All.push_back(I);
  }
  Local.clear();
}
