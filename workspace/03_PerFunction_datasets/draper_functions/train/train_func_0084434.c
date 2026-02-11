c2l (uint8_t *value, int size)
{
  int i, j;
  uint32_t res = 0;

  if (value)
    for (i = size - 1, j = 0; i >= 0; i--, j++)
      res += (*(value + j) << i * 8);

  return res;
}
