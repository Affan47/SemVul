amsync(A a, A aflags)
{
#ifdef _AIX
  R 0;
#else
  int bytes;

  unsigned long flags;

  if (SymbolsToMask(MsyncMasks, aflags, &flags) == -1) {
    (void)pa((V)aflags);
    q = ERR_DOMAIN;
    R 0;
  }
  bytes=mf_length(a);
  R bytes?msync((caddr_t)a, AH+Tt(a->t,a->n), (int)flags):0;
#endif
}
