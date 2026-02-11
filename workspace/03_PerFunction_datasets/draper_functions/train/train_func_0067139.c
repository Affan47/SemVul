remapFirstAddrForOwnerOnRestart()
{
  JASSERT(_isCkptLeader);
  ShmaddrToFlagIter i = _shmaddrToFlag.begin();
  void *tmpaddr = _real_shmat(_currentShmid, NULL, 0);
  JASSERT(tmpaddr != (void*) -1) (_currentShmid)(JASSERT_ERRNO);
  memcpy(tmpaddr, i->first, _size);
  JASSERT(_real_shmdt(tmpaddr) == 0);
  munmap(i->first, _size);

  if (!_dmtcpMappedAddr) {
    JASSERT (_real_shmat(_currentShmid, i->first, i->second) != (void *) -1);
  }
  JTRACE("Remapping shared memory segment")(_currentShmid);
}
