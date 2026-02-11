BinaryHeap_new(int (*cmp)(void*item1, void*item2)){
  BinaryHeap h;
  int max_len = 1<<8, i;

  h = MALLOC(sizeof(struct BinaryHeap_struct));
  h->max_len = max_len;
  h->len = 0;
  h->heap = MALLOC(sizeof(void*)*max_len);
  h->id_to_pos = MALLOC(sizeof(int)*max_len);
  for (i = 0; i < max_len; i++) (h->id_to_pos)[i] = -1;

  h->pos_to_id = MALLOC(sizeof(int)*max_len);
  h->id_stack = IntStack_new();
  h->cmp = cmp;
  return h;
}
