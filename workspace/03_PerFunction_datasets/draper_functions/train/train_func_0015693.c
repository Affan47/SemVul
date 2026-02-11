mailimf_body_parse(const char * message, size_t length,
		       size_t * index,
		       struct mailimf_body ** result)
{
  size_t cur_token;
  struct mailimf_body * body;

  cur_token = * index;

  body = mailimf_body_new(message + cur_token, length - cur_token);
  if (body == NULL)
    return MAILIMF_ERROR_MEMORY;

  cur_token = length;

  * result = body;
  * index = cur_token;

  return MAILIMF_NO_ERROR;
}
