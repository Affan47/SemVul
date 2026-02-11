gt_hpol_processor_subst_in_range(char *s, char *q,
    unsigned long left, unsigned long right, unsigned long length, char old,
    char new, char qual)
{
  unsigned long pos;
  for (pos = right + 1UL; pos > left && length > 0; )
  {
    pos--;
    if (s[pos] == old)
    {
      s[pos] = new;
      q[pos] = qual;
      length--;
    }
  }
  gt_assert(length == 0);
}
