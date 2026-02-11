list_ptr_step(List_ptr * ptr, int forward) {
  List_node *next;

  if (ptr->current == NULL) {
    return FALSE;
  }
  next = ptr->current->next;
  while (next != NULL && next->data == NULL) {
    if (forward) {
      next = next->next;
    } else {
      next = next->prev;
    }
  }
  if (next == NULL) {
    return FALSE;
  }

  list_node_unref(ptr->list, ptr->current);
  ptr->current = next;
  list_node_ref(ptr->list, ptr->current);
  return TRUE;
}
