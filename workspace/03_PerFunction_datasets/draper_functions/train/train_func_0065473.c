d_list_unshift(d_list_t *list, d_node_t *node) {
  if (NULL == list->head && NULL == list->tail) {
    list->head = node;
    list->tail = node;
    node->previous = NULL;
    node->next = NULL;
  } else {
    node->previous = list->tail;
    list->tail->next = node;
    node->next = NULL;
    list->tail = node;
  }
  list->size++;
}
