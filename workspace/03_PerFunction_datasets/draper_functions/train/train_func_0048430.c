gt_cstr_show(const char *cstr, unsigned long length, FILE *fp)
{
  unsigned long i;
  gt_assert(cstr && fp);
  for (i = 0; i < length; i++)
    gt_xfputc(cstr[i], fp);
}
