sigsuspend(const sigset_t *mask)
{
  if (mask != NULL) {
    sigset_t tmp = patchPOSIXMask(mask);
    mask = &tmp;
  }

  int ret = _real_sigsuspend(mask);
  return ret;
}
