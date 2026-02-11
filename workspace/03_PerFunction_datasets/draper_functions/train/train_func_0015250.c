str_rm_tail (char *str, const char* const charlist)
{
  int i;

  for (i = strlen(str) - 1; i >= 0; i--)
    if (strchr (charlist, str[i]) != NULL)
      str[i] = EOS;
    else
      break;

  return (str);
}
