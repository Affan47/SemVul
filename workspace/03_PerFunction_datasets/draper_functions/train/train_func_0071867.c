lua_dofile (char *filename)
{
  ZIO z;
  int status;
  int c;
  int bin;
  FILE *f = (filename == NULL) ? stdin : fopen(filename, "r");
  if (f == NULL)
    return 2;
  if (filename == NULL)
    filename = "(stdin)";
  c = fgetc(f);
  ungetc(c, f);
  bin = (c == ID_CHUNK);
  if (bin)
    f = freopen(filename, "rb", f);
  luaZ_Fopen(&z, f, filename);
  status = do_main(&z, bin);
  if (f != stdin)
    fclose(f);
  return status;
}
