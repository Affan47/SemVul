insert(pairlist x, pairlist list)
{
  if (! list) {
    x->next = NULL;
    return x;
  } else if (strcmp(x->name, list->name) <= 0) {
    x->next = list;
    return x;
  } else {
    list->next = insert(x, list->next);
    return list;
  }
}
