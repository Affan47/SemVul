preproc_evaluate_equal(
  PreprocessInfo *info, preproc_tokenizer *tokens,
  preproc_int_t *val, int *is_unsigned)
{
  int op;
  preproc_int_t rval;
  int rtype;
  int result;

  result = preproc_evaluate_compare(info, tokens, val, is_unsigned);
  while ((result & VTK_PARSE_FATAL_ERROR) == 0)
    {
    op = tokens->tok;
    if (op != TOK_EQ && op != TOK_NE)
      {
      return result;
      }

    preproc_next(tokens);

    result = preproc_evaluate_compare(info, tokens, &rval, &rtype);

    if (op == TOK_EQ)
      {
      *val = (*val == rval);
      }
    else if (op == TOK_NE)
      {
      *val = (*val != rval);
      }
    *is_unsigned = 0;
    }

  return result;
}
