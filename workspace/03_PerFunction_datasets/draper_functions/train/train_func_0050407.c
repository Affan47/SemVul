getPointerToGlobalIfAvailable(const GlobalValue *GV) {
  MutexGuard locked(lock);
  return getPointerToGlobalIfAvailable(getMangledName(GV));
}
