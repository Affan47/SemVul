confinit(c, filename, line, p, s)
  struct conf *c;
  char *filename;
  unsigned line;
  char *p;
  unsigned s;
{
  unsigned i;

  c->c_weight=0U;
  for(i=0U; i<CSIZE; ++i) strinit(&c->c_field[i]);
  strinit(&c->c_file);

  return confparse(c, filename, line, p, s);
}
