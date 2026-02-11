input_file_get (char *buf, size_t buflen)
{
  size_t size;

  if (feof (f_in))
    return 0;

  size = fread (buf, sizeof (char), buflen, f_in);
  if (ferror (f_in))
    as_bad (_("can't read from %s: %s"), file_name, xstrerror (errno));
  return size;
}
