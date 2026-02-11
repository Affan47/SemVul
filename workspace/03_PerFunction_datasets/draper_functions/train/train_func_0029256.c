append_include_chain (first, last)
     struct file_name_list *first, *last;
{
  struct file_name_list *dir;

  if (!first || !last)
    return;

  if (include == 0)
    include = first;
  else
    last_include->next = first;

  if (first_bracket_include == 0)
    first_bracket_include = first;

  for (dir = first; ; dir = dir->next) {
    int len = strlen (dir->fname) + INCLUDE_LEN_FUDGE;
    if (len > max_include_len)
      max_include_len = len;
    if (dir == last)
      break;
  }

  last->next = NULL;
  last_include = last;
}
