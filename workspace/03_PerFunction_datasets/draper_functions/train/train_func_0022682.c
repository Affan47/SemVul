mailmime_type_parse(const char * message, size_t length,
			       size_t * indx,
			       struct mailmime_type ** result)
{
  struct mailmime_discrete_type * discrete_type;
  struct mailmime_composite_type * composite_type;
  size_t cur_token;
  struct mailmime_type * mime_type;
  int type;
  int res;
  int r;

  cur_token = * indx;

  discrete_type = NULL;
  composite_type = NULL;

  type = MAILMIME_TYPE_ERROR;

  r = mailmime_composite_type_parse(message, length, &cur_token,
				    &composite_type);
  if (r == MAILIMF_NO_ERROR)
    type = MAILMIME_TYPE_COMPOSITE_TYPE;

  if (r == MAILIMF_ERROR_PARSE) {
    r = mailmime_discrete_type_parse(message, length, &cur_token,
				     &discrete_type);
    if (r == MAILIMF_NO_ERROR)
      type = MAILMIME_TYPE_DISCRETE_TYPE;
  }

  if (r != MAILIMF_NO_ERROR) {
    res = r;
    goto err;
  }

  mime_type = mailmime_type_new(type, discrete_type, composite_type);
  if (mime_type == NULL) {
    res = r;
    goto free;
  }

  * result = mime_type;
  * indx = cur_token;

  return MAILIMF_NO_ERROR;

 free:
  if (discrete_type != NULL)
    mailmime_discrete_type_free(discrete_type);
  if (composite_type != NULL)
    mailmime_composite_type_free(composite_type);
 err:
  return res;
}
