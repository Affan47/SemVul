fillbuf (buf, fp)
     struct buffer *buf;
     FILE *fp;
{
  int cc;

  memmove (buf->buf, buf->buf + buf->used - buf->left, buf->left);
  buf->used = buf->left;

#ifdef SAOMOD_BINARY
  if ( BinarySort ) {
	cc = fread (buf->buf + buf->used, 1, buf->alloc - buf->used, fp);

	buf->used += cc;

	return buf->used;
  }
#endif

  while (!feof (fp) && (buf->used == 0 || !memchr (buf->buf, '\n', buf->used)))
    {
      if (buf->used == buf->alloc)
	{
	  buf->alloc *= 2;
	  buf->buf = xrealloc (buf->buf, buf->alloc);
	}
      cc = fread (buf->buf + buf->used, 1, buf->alloc - buf->used, fp);
      if (ferror (fp))
	{
	  perror ("reading file");
	  cleanup ();
	  exit (2);
	}
      buf->used += cc;
    }

  if (feof (fp) && buf->used && buf->buf[buf->used - 1] != '\n')
    {
      if (buf->used == buf->alloc)
	{
	  buf->alloc *= 2;
	  buf->buf = xrealloc (buf->buf, buf->alloc);
	}
      buf->buf[buf->used++] = '\n';
    }

  return buf->used;
}
