memtest (uint8_t *data, unsigned int val, unsigned int len)
{
  unsigned int	i;

  for (i = 0; i < len; i++)
    if (data[i] != val)
      return -1;

  return 0;
}
