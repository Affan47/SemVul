preproc_evaluate_bitshift(
  PreprocessInfo *info, preproc_tokenizer *tokens,
  preproc_int_t *val, int *is_unsigned)
{
  int op;
  preproc_int_t rval;
  int rtype;
  int result;

  result = preproc_evaluate_add(info, tokens, val, is_unsigned);
  while ((result & VTK_PARSE_FATAL_ERROR) == 0)
    {
    op = tokens->tok;

    if (op != TOK_RSHIFT && op != TOK_LSHIFT)
      {
      return result;
      }

    preproc_next(tokens);

    result = preproc_evaluate_add(info, tokens, &rval, &rtype);

    if (*is_unsigned)
      {
      if (op == TOK_RSHIFT)
        {
        *val = (preproc_int_t)((preproc_uint_t)*val << rval);
        }
      else if (op == TOK_LSHIFT)
        {
        *val = (preproc_int_t)((preproc_uint_t)*val >> rval);
        }
      }
    else
      {
      if (op == TOK_RSHIFT)
        {
        *val = *val << rval;
        }
      else if (op == TOK_LSHIFT)
        {
        *val = *val >> rval;
        }
      }
    }

  return result;
}
