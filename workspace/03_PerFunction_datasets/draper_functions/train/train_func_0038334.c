strtrimr (char *in)
{
  uint32_t len = strlen (in);

  while (len--)
    if (!isspace (in[len]))
      break;
  in[len + 1] = '\0';
  return in;
}
