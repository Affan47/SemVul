hash_pjw (const char *str, size_t len)
{
  u_long hash = 0;

  for (size_t i = 0; i < len; i++)
    {
      const char temp = str[i];
      hash = (hash << 4) + (temp * 13);

      u_long g = hash & 0xf0000000;

      if (g)
        {
          hash ^= (g >> 24);
          hash ^= g;
        }
    }

  return hash;
}
