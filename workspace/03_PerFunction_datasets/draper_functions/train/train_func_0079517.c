verifyBBInRegion(BasicBlock *BB) const {
  if (!contains(BB))
    llvm_unreachable("Broken region found!");

  BasicBlock *entry = getEntry(), *exit = getExit();

  for (succ_iterator SI = succ_begin(BB), SE = succ_end(BB); SI != SE; ++SI)
    if (!contains(*SI) && exit != *SI)
      llvm_unreachable("Broken region found!");

  if (entry != BB)
    for (pred_iterator SI = pred_begin(BB), SE = pred_end(BB); SI != SE; ++SI)
      if (!contains(*SI))
        llvm_unreachable("Broken region found!");
}
