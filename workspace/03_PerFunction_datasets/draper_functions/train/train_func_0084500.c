checked_print_quoted (struct format_val *dest,
			   const char *format, const char *s)
{
  int rv = print_quoted(dest->stream, dest->quote_opts, dest->dest_is_tty,
			format, s);
  if (rv < 0)
    nonfatal_file_error(dest->filename);
}
