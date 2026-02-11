httpSetLength(http_t *http,
              size_t length)
{
  DEBUG_printf(("httpSetLength(http=%p, length=" CUPS_LLFMT ")", http,
                CUPS_LLCAST length));

  if (!http)
    return;

  if (!length)
  {
    strlcpy(http->fields[HTTP_FIELD_TRANSFER_ENCODING], "chunked",
            HTTP_MAX_VALUE);
    http->fields[HTTP_FIELD_CONTENT_LENGTH][0] = '\0';
  }
  else
  {
    http->fields[HTTP_FIELD_TRANSFER_ENCODING][0] = '\0';
    snprintf(http->fields[HTTP_FIELD_CONTENT_LENGTH], HTTP_MAX_VALUE,
             CUPS_LLFMT, CUPS_LLCAST length);
  }
}
