io_appendto (void)
{
  char *s = luaL_check_string(FIRSTARG);
  FILE *fp = fopen (s, "a");
  if (fp != NULL)
    setreturn(fp, FOUTPUT);
  else
    pushresult(0);
}
