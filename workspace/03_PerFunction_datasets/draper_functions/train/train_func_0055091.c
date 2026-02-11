body_to_mmapstr(char * data, size_t size,
    char ** result, size_t * result_len)
{
  MMAPString * mmapstr;
  size_t cur_token;
  int res;
  int r;

  cur_token = 0;


  while (1) {
    r = mailimf_ignore_field_parse(data, size, &cur_token);
    if (r == MAILIMF_NO_ERROR) {

    }
    else
      break;
  }

  r = mailimf_crlf_parse(data, size, &cur_token);
  if ((r != MAILIMF_NO_ERROR) && (r != MAILIMF_ERROR_PARSE)) {
    res = maildriver_imf_error_to_mail_error(r);
    goto err;
  }

  mmapstr = mmap_string_new_len(data + cur_token, size - cur_token);
  if (mmapstr == NULL) {
    res = MAIL_ERROR_MEMORY;

    goto err;
  }

  r = mmap_string_ref(mmapstr);
  if (r != 0) {
    mmap_string_free(mmapstr);
    res = MAIL_ERROR_MEMORY;

    goto err;
  }

  * result = mmapstr->str;
  * result_len = mmapstr->len;

  return MAIL_NO_ERROR;

 err:
  return res;
}
