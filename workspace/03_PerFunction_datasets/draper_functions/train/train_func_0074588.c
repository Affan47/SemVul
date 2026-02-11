removeModule(Module *M) {
  MutexGuard locked(lock);
  return OwnedModules.removeModule(M);
}
