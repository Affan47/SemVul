get_void_list_element(void)
{
  VOID_LIST_ELEMENT  *list;
  const int          n_elements = 20;
  int                i;

  if (!first_element)
  {
    first_element = MEM_ALLOC(n_elements, VOID_LIST_ELEMENT);
    for (i = 0; i < n_elements-1; i++)
    {
      first_element[i].data = nil;
      first_element[i].next = first_element+(i+1);
    }
    first_element[n_elements-1].data = nil;
    first_element[n_elements-1].next = nil;
  }
  list = first_element;
  first_element = list->next;

  list->next = nil;
  return(list);
}
