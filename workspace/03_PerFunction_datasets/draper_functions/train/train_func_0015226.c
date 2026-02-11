neo_cursor_add_result(neo_cursor *cursor, neo_data *data) {
  if(cursor->head == NULL) {
    cursor->head = malloc(sizeof(neo_elem));
    cursor->head->data = data;
    cursor->head->next = NULL;
    cursor->tail = cursor->head;
  } else {
    cursor->tail->next = malloc(sizeof(neo_cursor));
    cursor->tail = cursor->tail->next;
    cursor->tail->next = NULL;
    cursor->tail->data = data;
  }
}
