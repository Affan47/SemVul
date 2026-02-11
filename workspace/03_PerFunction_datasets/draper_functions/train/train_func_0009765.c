mktempfile(char *filename)
{
  char rands[8], *tempname, *fn = filename;
  int l;

  make_rand_str(rands, 7);
  l = strlen(filename);
  if ((l + MKTEMPFILE_TOT) > NAME_MAX) {
    fn[NAME_MAX - MKTEMPFILE_TOT] = 0;
    l = NAME_MAX - MKTEMPFILE_TOT;
    fn = nmalloc(l + 1);
    strncpy(fn, filename, l);
    fn[l] = 0;
  }
  tempname = nmalloc(l + MKTEMPFILE_TOT + 1);
  sprintf(tempname, "%u-%s-%s", getpid(), rands, fn);
  if (fn != filename)
    my_free(fn);
  return tempname;
}
