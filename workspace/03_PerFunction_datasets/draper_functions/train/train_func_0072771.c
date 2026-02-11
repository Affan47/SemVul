es_print (estream_t ES__RESTRICT stream,
	  const char *ES__RESTRICT format, va_list ap)
{
  int rc;

  stream->intern->print_ntotal = 0;
  rc = estream_format (print_writer, stream, format, ap);
  if (rc)
    return -1;
  return (int)stream->intern->print_ntotal;
}
