inf_discard_tokens(struct inputfile *inf, enum inf_token_type type)
{
  int count = 0;

  while(inf_token(inf, type))
    count++;
  return count;
}
