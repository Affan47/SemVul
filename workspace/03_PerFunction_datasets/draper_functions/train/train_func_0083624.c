addGlobalMapping(const GlobalValue *GV, void *Addr) {
  MutexGuard locked(lock);
  addGlobalMapping(getMangledName(GV), (uint64_t) Addr);
}
