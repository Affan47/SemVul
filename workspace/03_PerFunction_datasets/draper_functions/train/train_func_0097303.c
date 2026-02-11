thumb_fmt(unsigned char *buf, size_t buflen)
{
  char *p, *s;
  Ds *ds;

  s = strbtohex(buf, buflen, STRBTOHEX_UPPER);

  ds = ds_init(NULL);
  for (p = s; *p != '\0'; p++) {
	if (p != s)
	  ds_appendc(ds, (int) ':');
	ds_appendc(ds, (int) *p++);
	ds_appendc(ds, (int) *p);
  }
  ds_appendc(ds, (int) '\0');

  return(ds);
}
