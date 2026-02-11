pthread_rwlockattr_setpshared (attr, pshared)
     pthread_rwlockattr_t *attr;
     int pshared;
{
  struct pthread_rwlockattr *iattr;

  if (pshared != PTHREAD_PROCESS_SHARED
      && __builtin_expect (pshared != PTHREAD_PROCESS_PRIVATE, 0))
    return EINVAL;

  iattr = (struct pthread_rwlockattr *) attr;

  iattr->pshared = pshared;

  return 0;
}
