list_ptr_getend(List_ptr * ptr, int head) {
  List_node *next;

  if (head) {
    next = ptr->list->head;
  } else {
    next = ptr->list->tail;
  }

  while (next != NULL && next->data == NULL) {
    if (head) {
      next = next->next;
    } else {
      next = next->prev;
    }
  }
  if (next == NULL) {
    return FALSE;
  }
  if (ptr->current != NULL) {
    list_node_unref(ptr->list, ptr->current);
  }
  ptr->current = next;
  list_node_ref(ptr->list, ptr->current);
  return TRUE;
}
