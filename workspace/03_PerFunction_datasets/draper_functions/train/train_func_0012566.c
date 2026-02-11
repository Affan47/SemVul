MarkAliveBlocks(BasicBlock *BB,
                            SmallPtrSet<BasicBlock*, 128> &Reachable) {

  SmallVector<BasicBlock*, 128> Worklist;
  Worklist.push_back(BB);
  bool Changed = false;
  do {
    BB = Worklist.pop_back_val();

    if (!Reachable.insert(BB))
      continue;


    for (BasicBlock::iterator BBI = BB->begin(), E = BB->end(); BBI != E;++BBI){
      if (CallInst *CI = dyn_cast<CallInst>(BBI)) {
        if (CI->doesNotReturn()) {


          ++BBI;
          if (!isa<UnreachableInst>(BBI)) {

            ChangeToUnreachable(BBI, false);
            Changed = true;
          }
          break;
        }
      }


      if (StoreInst *SI = dyn_cast<StoreInst>(BBI)) {

        if (SI->isVolatile()) continue;

        Value *Ptr = SI->getOperand(1);

        if (isa<UndefValue>(Ptr) ||
            (isa<ConstantPointerNull>(Ptr) &&
             SI->getPointerAddressSpace() == 0)) {
          ChangeToUnreachable(SI, true);
          Changed = true;
          break;
        }
      }
    }


    if (InvokeInst *II = dyn_cast<InvokeInst>(BB->getTerminator()))
      if (II->doesNotThrow()) {
        ChangeToCall(II);
        Changed = true;
      }

    Changed |= ConstantFoldTerminator(BB, true);
    for (succ_iterator SI = succ_begin(BB), SE = succ_end(BB); SI != SE; ++SI)
      Worklist.push_back(*SI);
  } while (!Worklist.empty());
  return Changed;
}
