__readahead (int fd, off64_t offset, size_t count)
{
  return INLINE_SYSCALL (readahead, 4, fd,
			 __LONG_LONG_PAIR ((off_t) (offset >> 32),
					   (off_t) (offset & 0xffffffff)),
			 count);
}
