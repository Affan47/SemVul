find_parens(compile_data *cd, const uschar *name, int lorn, BOOL xmode)
{
uschar *ptr = (uschar *)cd->start_pattern;
int count = 0;
int rc;


for (;;)
  {
  rc = find_parens_sub(&ptr, cd, name, lorn, xmode, &count);
  if (rc > 0 || *ptr++ == 0) break;
  }

return rc;
}
