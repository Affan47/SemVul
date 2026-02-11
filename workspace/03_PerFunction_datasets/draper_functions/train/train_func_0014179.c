token_compare(const void *pa, const void *pb)
{
  const struct lexer_token *ta = pa;
  const struct lexer_token *tb = pb;
  unsigned int ii = 0;
  int res;
  while (ta->string[ii] && (ToLower(ta->string[ii]) == ToLower(tb->string[ii])))
    ii++;
  res = ToLower(tb->string[ii]) - ToLower(ta->string[ii]);
  return res;
}
