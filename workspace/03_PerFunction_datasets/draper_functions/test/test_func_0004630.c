ustat (dev_t dev, struct ustat *ubuf)
{
  unsigned long long int k_dev;


  k_dev =  dev & ((1ULL << 32) - 1);
  if (k_dev != dev)
    {
      __set_errno (EINVAL);
      return -1;
    }

  return INLINE_SYSCALL (ustat, 2, (unsigned int) k_dev, ubuf);
}
