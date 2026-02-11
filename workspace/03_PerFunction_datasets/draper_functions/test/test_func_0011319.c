is_getc (InputStream *is)
{
  int ch;

  if (is->unget_pos > 0)
    {
      ch = is->unget_ch[--is->unget_pos];
      return ch;
    }

 retry:


  if (is->bufpos >= is->data_in_buf)
    {

      if (is->nreads > 0 && is->data_in_buf < sizeof (is->buf))

	return EOF;


      is->data_in_buf = fread (is->buf, 1, sizeof (is->buf), is->fp);
      is->bufpos = 0;
      is->nreads++;

      goto retry;
    }

  return is->buf[is->bufpos++];
}
