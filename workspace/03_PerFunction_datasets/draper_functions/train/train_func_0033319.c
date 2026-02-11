getchr ()
{
  int ret;

  if (garglist == 0)
    return ('\0');

  ret = (int)garglist->word->word[0];
  garglist = garglist->next;
  return ret;
}
