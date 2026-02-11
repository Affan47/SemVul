token_list (CSTOKEN *tokens, int ntokens, char *buf, size_t buflen)
{
  char *p = buf;
  int i, t;
  char save;

  for (i = 0; i < ntokens && buflen > 0; i++)
  {
    if (tokens[i].value)
    {
      save = tokens[i].value[tokens[i].len];
      tokens[i].value[tokens[i].len] = '\0';
      t = snprintf(p, buflen, "%s%d:%s:'%s'", i ? "  ":"", i, expand_token_type(tokens[i].type, 0), tokens[i].value);
      tokens[i].value[tokens[i].len] = save;
    }
    else
    {
      t = snprintf(p, buflen, "%s%d:%s", i ? "  ":"", i, expand_token_type(tokens[i].type, 0));
    }
    if (t == -1 || t >= buflen) return buf;
    buflen -= t;
    p += t;
  }
  return buf;
}
