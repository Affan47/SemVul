mmap_gt_pch_use_address (void *base, size_t size, int fd, size_t offset)
{
  void *addr;


  if (size == 0)
    return -1;

  addr = mmap ((caddr_t) base, size, PROT_READ | PROT_WRITE, MAP_PRIVATE,
	       fd, offset);

  return addr == base ? 1 : -1;
}
