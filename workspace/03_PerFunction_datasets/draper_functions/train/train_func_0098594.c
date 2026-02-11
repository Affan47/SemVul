_k_circular_queue_realloc(KCircularQueue *q, unsigned int new_size)
{
  char         *newdata;
  unsigned int  till_end;

  newdata = malloc(q->el_size * new_size);

  till_end = q->allocated_size - q->first;
  memcpy(newdata, q->data + q->first*q->el_size, till_end*q->el_size);
  if (till_end < q->size) {
    memcpy(newdata + till_end*q->el_size,
           q->data,
           (q->size - till_end)*q->el_size);
  }

  q->allocated_size = new_size;
  q->first          = 0;
  q->first_free     = q->size;
  q->free_until_end = q->allocated_size - q->size;

  free(q->data);
  q->data = newdata;
}
