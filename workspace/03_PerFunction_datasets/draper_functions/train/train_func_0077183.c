CheckForEscapingAllocas(BasicBlock *BB,
                                    bool &CannotTCETailMarkedCall) {
  bool RetVal = false;
  for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; ++I)
    if (AllocaInst *AI = dyn_cast<AllocaInst>(I)) {
      RetVal |= AllocaMightEscapeToCalls(AI);


      if (BB != &BB->getParent()->getEntryBlock() ||
          !isa<ConstantInt>(AI->getArraySize()))
        CannotTCETailMarkedCall = true;
    }
  return RetVal;
}
