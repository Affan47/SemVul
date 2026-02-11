on_shmdt(const void *shmaddr)
{
  JASSERT(isValidShmaddr(shmaddr));
  _shmaddrToFlag.erase((void*)shmaddr);


}
