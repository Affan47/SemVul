ifile_lexer_email_prelex_header (ifile_lex *lex, ifile_lexer *self)
{
  int begin_unfinished;
  char *header, *body;
  int body_size;


  if (SELF->headers_to_keep == NULL
      || SELF->headers_to_keep == (char **) -1)
    return 0;
  if (lex->document_position != 0)
    return ERROR;

  begin_unfinished = 0;


  while (lex->document_position < lex->document_length
	 && lex->document[lex->document_position] != '\n')
    {
      if ((header = ifile_lexer_email_parse_header (lex, self)))
	{
	  if (header == (char *) ERROR) break;
	  strcpy (&lex->document[begin_unfinished], header);
	  begin_unfinished += strlen (header);
	  free (header);
	}
    }

  body_size = lex->document_length - lex->document_position;
  body = (char *) malloc (sizeof(char) * (body_size + 1));
  strncpy (body, &lex->document[lex->document_position], body_size);
  body[body_size] = '\0';
  strcpy (&lex->document[begin_unfinished], body);
  lex->document_length = begin_unfinished + body_size - 1;

  lex->document_position = 0;
  return 0;
}
