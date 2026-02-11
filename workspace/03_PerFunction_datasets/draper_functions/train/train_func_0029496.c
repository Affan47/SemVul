memzapb(void *s, int val, size_t len)
{
  volatile unsigned char *ptr = (volatile unsigned char *) s;
  size_t i;

  for (i = 0; i < len; i++)
	*ptr++ = val;
}
