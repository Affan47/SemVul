loader_BASICODE_check(const char *filename,
		      unsigned char *data,
		      long size)
{


  if (size >= 5)
    if (memcmp(data, "1000 ", 5) == 0)
      return 1;

  return 0;
}
