getGOTIndexForAddr(void* addr) {
  unsigned idx = revGOTMap[addr];
  if (!idx) {
    idx = ++nextGOTIndex;
    revGOTMap[addr] = idx;
    DEBUG(dbgs() << "JIT: Adding GOT entry " << idx << " for addr ["
                 << addr << "]\n");
  }
  return idx;
}
