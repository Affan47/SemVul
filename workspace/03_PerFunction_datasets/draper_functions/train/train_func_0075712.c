list_node_unref(List * list, List_node * item) {

  item->refcount--;
  if (item->refcount <= 0) {
    if (item->next != NULL) {
      item->next->prev = item->prev;
    }
    if (item->prev != NULL) {
      item->prev->next = item->next;
    }
    if (list->head == item) {
      list->head = item->next;
    }
    if (list->tail == item) {
      list->tail = item->prev;
    }
    free(item);
  }
}
