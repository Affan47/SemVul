releaseMemory() {

  if (PImpl) {
    delete &getCache(PImpl);
    PImpl = 0;
  }
}
