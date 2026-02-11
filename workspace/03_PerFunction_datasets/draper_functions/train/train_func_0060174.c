useFuncSeen(const Constant *C,
                        llvm::DenseMap<const Function *, bool> &seenMap) {
  for (const User *U : C->users()) {
    if (const Constant *cu = dyn_cast<Constant>(U)) {
      if (useFuncSeen(cu, seenMap))
        return true;
    } else if (const Instruction *I = dyn_cast<Instruction>(U)) {
      const BasicBlock *bb = I->getParent();
      if (!bb)
        continue;
      const Function *caller = bb->getParent();
      if (!caller)
        continue;
      if (seenMap.find(caller) != seenMap.end())
        return true;
    }
  }
  return false;
}
