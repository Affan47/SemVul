builtin_macro (pfile, node)
     cpp_reader *pfile;
     cpp_hashnode *node;
{
  const uchar *buf;

  if (node->value.builtin == BT_PRAGMA)
    {


      if (pfile->state.in_directive)
	return 0;

      _cpp_do__Pragma (pfile);
      return 1;
    }

  buf = _cpp_builtin_macro_text (pfile, node);

  cpp_push_buffer (pfile, buf, ustrlen (buf),  true, 1);


  pfile->buffer->col_adjust = pfile->cur_token[-1].col - 1;


  pfile->buffer->saved_flags = 0;


  pfile->cur_token = _cpp_temp_token (pfile);
  push_token_context (pfile, NULL, _cpp_lex_direct (pfile), 1);
  if (pfile->buffer->cur != pfile->buffer->rlimit)
    cpp_error (pfile, DL_ICE, "invalid built-in macro \"%s\"",
	       NODE_NAME (node));
  _cpp_pop_buffer (pfile);

  return 1;
}
