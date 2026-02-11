copy_list (Keyword_List *list)
{
  Keyword_List *result;
  Keyword_List **lastp = &result;
  while (list != NULL)
    {
      Keyword_List *new_cons = new Keyword_List (list->first());
      *lastp = new_cons;
      lastp = &new_cons->rest();
      list = list->rest();
    }
  *lastp = NULL;
  return result;
}
