search_list_append (Search_List *list, const char *paths)
{
  Search_List_Elem *new_el;
  const char *beg, *colon;
  unsigned int len;

  colon = paths - 1;
  do
    {
      beg = colon + 1;
      colon = strchr (beg, PATH_SEP_CHAR);

      if (colon)
	len = colon - beg;
      else
	len = strlen (beg);

      new_el = (Search_List_Elem *) xmalloc (sizeof (*new_el) + len);
      memcpy (new_el->path, beg, len);
      new_el->path[len] = '\0';


      new_el->next = 0;

      if (list->tail)
	list->tail->next = new_el;
      else
	list->head = new_el;

      list->tail = new_el;
    }
  while (colon);
}
