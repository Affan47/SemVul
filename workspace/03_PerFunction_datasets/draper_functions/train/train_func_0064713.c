d_list_destroy(d_list_t *list) {
  d_node_t * node = list->head;
  d_node_t * tmp = NULL;
  while (NULL != node) {
    tmp = node->next;
    d_node_destroy(node);
    node = tmp;
  }
  free(list);
}
