sort_char_set (unsigned int *base, int len)
{

  for (int i = 1; i < len; i++)
    {
      int j;
      unsigned int tmp;

      for (j = i, tmp = base[j]; j > 0 && tmp < base[j - 1]; j--)
        base[j] = base[j - 1];

      base[j] = tmp;
    }
}
