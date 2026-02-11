read_entry(FILE * fp, int *r, int *g, int *b, char *name)
{
  int  n;
  char buf[512], *p;

  if (!fgets(buf, sizeof(buf) - 1, fp))
    return 0;

  if(buf[0] == '!') {
    if (fgets(buf,sizeof(buf)-1,fp)==0) {

    }
  }

  if(sscanf(buf, " %d %d %d %n", r, g, b, &n) < 3)
    return 0;

  p = buf + n;


  while (*p)
  {
    if (*p != ' ' && *p != '\n')
      *name++ = *p;
    p++;
  }
  *name = 0;

  return (feof(fp) || ferror(fp)) ? 0 : 1;
}
