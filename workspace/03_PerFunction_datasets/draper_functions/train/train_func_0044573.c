__ftruncate64 (int fd, off64_t length)
{
  unsigned int low = length & 0xffffffff;
  unsigned int high = length >> 32;
  int result = INLINE_SYSCALL (ftruncate64, 3, fd,
			       __LONG_LONG_PAIR (high, low));
  return result;
}
