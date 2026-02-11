mailimf_cache_string_write(MMAPString * mmapstr, size_t * indx,
			       char * str, size_t length)
{
  int r;

  if (str == NULL) {
    r = mailimf_cache_int_write(mmapstr, indx, CACHE_NULL_POINTER);
    if (r != MAIL_NO_ERROR)
      return r;
  }
  else {
    r = mailimf_cache_int_write(mmapstr, indx, CACHE_NOT_NULL);
    if (r != MAIL_NO_ERROR)
      return r;

    r = mailimf_cache_int_write(mmapstr, indx, length);
    if (r != MAIL_NO_ERROR)
      return r;

    if (length != 0) {
      r = mail_serialize_write(mmapstr, indx, str, length);
      if (r != MAIL_NO_ERROR)
        return MAIL_ERROR_FILE;
    }
  }

  return MAIL_NO_ERROR;
}
