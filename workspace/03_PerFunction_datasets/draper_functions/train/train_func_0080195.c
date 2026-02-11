tuple_formatter_compile(TupleEvalContext *ctx, const char *expr)
{
  int level = 0;
  const char *tmpexpr = expr;
  TupleEvalNode *res1;

  res1 = tuple_compiler_pass1(&level, ctx, &tmpexpr);

  if (level != 1) {
    tuple_error(ctx, "Syntax error! Uneven/unmatched nesting of elements! (%d)\n", level);
    tuple_evalnode_free(res1);
    return NULL;
  }

  return res1;
}
