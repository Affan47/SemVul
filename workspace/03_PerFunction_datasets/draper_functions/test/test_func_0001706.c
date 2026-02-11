cbf_is_mimebinary (cbf_node *column, unsigned int row)
{
  const char *text;


  if (cbf_get_columnrow (&text, column, row))

   return 0;

  if (text)

    return (*text == CBF_TOKEN_MIME_BIN);


  return 0;
}
