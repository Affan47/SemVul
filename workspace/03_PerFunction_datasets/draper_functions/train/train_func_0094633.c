cupsFileWrite(cups_file_t *fp,
              const char  *buf,
	      size_t      bytes)
{


  DEBUG_printf(("2cupsFileWrite(fp=%p, buf=%p, bytes=" CUPS_LLFMT ")",
                fp, buf, CUPS_LLCAST bytes));

  if (!fp || !buf || (fp->mode != 'w' && fp->mode != 's'))
    return (-1);

  if (bytes == 0)
    return (0);


  if (fp->mode == 's')
  {
    if (cups_write(fp, buf, bytes) < 0)
      return (-1);

    fp->pos += (off_t)bytes;

    DEBUG_printf(("4cupsFileWrite: pos=" CUPS_LLFMT, CUPS_LLCAST fp->pos));

    return ((ssize_t)bytes);
  }

  if ((fp->ptr + bytes) > fp->end)
    if (cupsFileFlush(fp))
      return (-1);

  fp->pos += (off_t)bytes;

  DEBUG_printf(("4cupsFileWrite: pos=" CUPS_LLFMT, CUPS_LLCAST fp->pos));

  if (bytes > sizeof(fp->buf))
  {
#ifdef HAVE_LIBZ
    if (fp->compressed)
      return (cups_compress(fp, buf, bytes));
    else
#endif
      return (cups_write(fp, buf, bytes));
  }
  else
  {
    memcpy(fp->ptr, buf, bytes);
    fp->ptr += bytes;
    return ((ssize_t)bytes);
  }
}
