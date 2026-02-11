cupsFileFlush(cups_file_t *fp)
{
  ssize_t	bytes;


  DEBUG_printf(("cupsFileFlush(fp=%p)", fp));


  if (!fp || fp->mode != 'w')
  {
    DEBUG_puts("1cupsFileFlush: Attempt to flush a read-only file...");
    return (-1);
  }

  bytes = (ssize_t)(fp->ptr - fp->buf);

  DEBUG_printf(("2cupsFileFlush: Flushing " CUPS_LLFMT " bytes...",
                CUPS_LLCAST bytes));

  if (bytes > 0)
  {
#ifdef HAVE_LIBZ
    if (fp->compressed)
      bytes = cups_compress(fp, fp->buf, bytes);
    else
#endif
      bytes = cups_write(fp, fp->buf, bytes);

    if (bytes < 0)
      return (-1);

    fp->ptr = fp->buf;
  }

  return (0);
}
