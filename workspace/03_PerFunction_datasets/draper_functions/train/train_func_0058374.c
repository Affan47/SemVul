__sigblock (mask)
     int mask;
{
  sigset_t set, oset;

  if (sigset_set_old_mask (&set, mask) < 0)
    return -1;

  if (__sigprocmask (SIG_BLOCK, &set, &oset) < 0)
    return -1;

  return sigset_get_old_mask (&oset);
}
