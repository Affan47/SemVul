mailmime_text_content_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col, int encoding,
				       int istext,
				       const char * text, size_t size)
{
  switch (encoding) {
  case MAILMIME_MECHANISM_QUOTED_PRINTABLE:
    return mailmime_quoted_printable_write_driver(do_write, data, col, istext, text, size);
    break;

  case MAILMIME_MECHANISM_BASE64:
    return mailmime_base64_write_driver(do_write, data, col, text, size);
    break;

  case MAILMIME_MECHANISM_7BIT:
  case MAILMIME_MECHANISM_8BIT:
  case MAILMIME_MECHANISM_BINARY:
  default:
    return mailimf_string_write_driver(do_write, data, col, text, size);
  }
}
