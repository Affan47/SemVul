grow_outbuf (obuf, needed)
     register FILE_BUF *obuf;
     register int needed;
{
  register U_CHAR *p;
  int minsize;

  if (obuf->length - (obuf->bufp - obuf->buf) > needed)
    return 0;


  obuf->length *= 2;

  minsize = (3 * needed) / 2 + (obuf->bufp - obuf->buf);
  if (minsize > obuf->length)
    obuf->length = minsize;

  if ((p = (U_CHAR *) xrealloc (obuf->buf, obuf->length)) == NULL)
    memory_full ();

  obuf->bufp = p + (obuf->bufp - obuf->buf);
  obuf->buf = p;

  return 0;
}
