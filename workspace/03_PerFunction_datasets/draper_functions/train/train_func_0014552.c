addModule(std::unique_ptr<Module> M) {
  MutexGuard locked(lock);
  OwnedModules.addModule(std::move(M));
}
