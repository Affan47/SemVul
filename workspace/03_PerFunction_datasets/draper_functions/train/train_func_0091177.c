httpSetField(http_t       *http,
             http_field_t field,
	     const char   *value)
{
  if (http == NULL ||
      field < HTTP_FIELD_ACCEPT_LANGUAGE ||
      field > HTTP_FIELD_WWW_AUTHENTICATE ||
      value == NULL)
    return;

  strlcpy(http->fields[field], value, HTTP_MAX_VALUE);
}
