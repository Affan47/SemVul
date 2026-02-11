latin1_to_utf8(char* source)
{
  int cur_alloc_size = 512;
  const int step = 256;
  unsigned char* dest = xmalloc(cur_alloc_size);
  unsigned char* pcs = (unsigned char*) source;
  unsigned char* pcd = (unsigned char*) dest;
  unsigned char* pcd_limit = pcd + cur_alloc_size;
  while(*pcs != '\0')
    {
      if (pcd == pcd_limit)
	{
	  cur_alloc_size += step;
	  dest = xrealloc(dest, cur_alloc_size);
	  pcd = dest + cur_alloc_size - step;
	  pcd_limit = pcd + step;
	}
      if (*pcs < 128)
	{
	  *pcd = *pcs;
	  pcs++;
	  pcd++;
	}
      else
	{
	  *pcd = 0xc2 + ((*pcs - 128) / 64);
	  pcd++;
	  *pcd = 0x80 + ((*pcs - 128) % 64);
	  pcd++;
	  pcs++;
	}
    }
  *pcd = '\0';
  return (char*)dest;
}
