loadRAM(const char *filename)
{
  if (filename == NULL)
    return;

  long addr = 0;
  const char *ptr = strstr(filename, "0x");
  if (ptr != NULL)
    addr = strtol(ptr, NULL, 0) & 0xffff;

  loadRAM(filename, addr);
}
