PriorityQueue_pop(PriorityQueue q, int *i, int *gain){
  int gain_max;
  DoubleLinkedList l;
  int *data;

  if (!q || q->count <= 0) return 0;
  *gain = gain_max = q->gain_max;
  (q->count)--;
  l = (q->buckets)[gain_max];
  data = (int*) DoubleLinkedList_get_data(l);
  *i = data[0];

  DoubleLinkedList_delete_element(l, free, &((q->buckets)[gain_max]));
  if (!(q->buckets)[gain_max]){
    while (gain_max >= 0 && !(q->buckets)[gain_max]) gain_max--;
    q->gain_max = gain_max;
  }
  q->where[*i] = NULL;
  q->gain[*i] = -999;
  return 1;
}
