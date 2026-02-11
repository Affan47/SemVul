preproc_evaluate_unary(
  PreprocessInfo *info, preproc_tokenizer *tokens,
  preproc_int_t *val, int *is_unsigned)
{
  int op = tokens->tok;
  int result = VTK_PARSE_OK;

  if (op != '+' && op != '-' && op != '~' && op != '!')
    {
    return preproc_evaluate_single(info, tokens, val, is_unsigned);
    }

  preproc_next(tokens);

  result = preproc_evaluate_unary(info, tokens, val, is_unsigned);
  if ((result & VTK_PARSE_FATAL_ERROR) == 0)
    {
    if (op == '~') { *val = ~(*val); }
    else if (op == '!') { *val = !(*val); *is_unsigned = 0; }
    else if (op == '-') { *val = -(*val); }
    return result;
    }

  return result;
}
