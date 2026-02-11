xmember(const sigset_t *set, int sig)
{
  unsigned rv;


  rv = sigismember(set, sig);
  if (rv > 1)
    abort();

  return rv;
}
