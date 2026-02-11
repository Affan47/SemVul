MOOVar_listindex(MOOVar * list, int index) {
  MOOVar *v;
  int i;

  if (list->type != LIST || index < 1 || index > list->i)
    return NULL;
  v = list->list;
  for (i = 1; i < index; i++) {
    v = v->next;
  }
  return v;
}
