create_token(char *name)
{
  int result;
  if (ntokens == maxtokens) {
    grow_tokens();
  }
  result = ntokens++;
  toktable[result] = new_string(name);
  return result;
}
