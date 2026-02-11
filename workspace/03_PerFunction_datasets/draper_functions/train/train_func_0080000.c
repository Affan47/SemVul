sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
  const sigset_t *orig = set;
  if (set != NULL) {
    sigset_t tmp = patchPOSIXMask(set);
    set = &tmp;
  }

  int ret = _real_sigprocmask( how, set, oldset );

  if (ret != -1) {
    patchPOSIXUserMask(how, orig, oldset);
  }
  return ret;
}
