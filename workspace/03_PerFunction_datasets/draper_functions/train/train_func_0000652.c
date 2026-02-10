runOnModule(Module &M) {
  bool Changed = false;
  bool LocalChange = true;


  while (LocalChange) {
    LocalChange = false;
    for (Module::iterator I = M.begin(), E = M.end(); I != E; ++I)
      if (!I->isDeclaration()) {

        I->removeDeadConstantUsers();
        if (I->hasLocalLinkage())
          LocalChange |= PropagateConstantsIntoArguments(*I);
        Changed |= PropagateConstantReturn(*I);
      }
    Changed |= LocalChange;
  }
  return Changed;
}
