save_comment (pfile, token, from, type)
     cpp_reader *pfile;
     cpp_token *token;
     const unsigned char *from;
     cppchar_t type;
{
  unsigned char *buffer;
  unsigned int len, clen;

  len = pfile->buffer->cur - from + 1;


  if (is_vspace (pfile->buffer->cur[-1]))
    len--;


  clen = (pfile->state.in_directive && type == '/') ? len + 2 : len;

  buffer = _cpp_unaligned_alloc (pfile, clen);

  token->type = CPP_COMMENT;
  token->val.str.len = clen;
  token->val.str.text = buffer;

  buffer[0] = '/';
  memcpy (buffer + 1, from, len - 1);


  if (pfile->state.in_directive && type == '/')
    {
      buffer[1] = '*';
      buffer[clen - 2] = '*';
      buffer[clen - 1] = '/';
    }
}
