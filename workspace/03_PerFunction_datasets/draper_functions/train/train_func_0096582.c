doInitialization(Module &M) {
  bool Changed = false;

  dumpArguments();
  dumpPasses();

  for (ImmutablePass *ImPass : getImmutablePasses())
    Changed |= ImPass->doInitialization(M);

  for (unsigned Index = 0; Index < getNumContainedManagers(); ++Index)
    Changed |= getContainedManager(Index)->doInitialization(M);

  return Changed;
}
