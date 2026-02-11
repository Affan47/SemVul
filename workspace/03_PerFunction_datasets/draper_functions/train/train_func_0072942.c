dsio_set(Ds *ds, FILE *fp, char *buf, unsigned long len, int have_length)
{
  Dsio *in;

  if ((fp == NULL && buf == NULL) || (fp != NULL && buf != NULL))
    return(NULL);

  if (ds->io == NULL)
	in = ds->io = ALLOC(Dsio);
  else
	in = ds->io;

  in->fp = fp;
  in->buf = in->ptr = buf;

  if (buf != NULL && have_length == 0) {
	in->length = in->rem = strlen(buf);
	in->have_length = 1;
  }
  else {
	in->length = in->rem = len;
	in->have_length = have_length;
  }

  in->got_peeked_char = 0;
  in->peeked_char = 0;

  return(in);
}
