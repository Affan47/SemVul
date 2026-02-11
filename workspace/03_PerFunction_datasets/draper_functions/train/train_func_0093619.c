closefile (FILE *f)
{
  if (f == stdin || f == stdout)
    return;
  if (f == lua_infile)
    lua_infile = stdin;
  if (f == lua_outfile)
    lua_outfile = stdout;
  if (pclose(f) == -1)
    fclose(f);
}
