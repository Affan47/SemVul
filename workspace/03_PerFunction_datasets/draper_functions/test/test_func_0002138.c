ascii2uint64(char *buffer, int digits)
{

  unsigned int ret = 0;
  char *b = buffer;

  for(int i=0; i<digits; i++)
    ret = (ret << 4) + a2i(*b++);

  return ret;
}
