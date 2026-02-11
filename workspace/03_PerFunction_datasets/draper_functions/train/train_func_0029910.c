STREAM_unmap(char *addr, int len)
{
  if (addr && len > 0 && ARCHIVE_check_addr(addr))
  {
  	munmap(addr, len);
	}
}
