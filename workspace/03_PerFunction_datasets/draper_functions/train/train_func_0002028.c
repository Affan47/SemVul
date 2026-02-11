lto_tag_check_set (enum LTO_tags actual, int ntags, ...)
{
  va_list ap;
  int i;

  va_start (ap, ntags);
  for (i = 0; i < ntags; i++)
    if ((unsigned) actual == va_arg (ap, unsigned))
      {
	va_end (ap);
	return;
      }

  va_end (ap);
  internal_error ("bytecode stream: unexpected tag %s", lto_tag_name (actual));
}
