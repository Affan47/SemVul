dict_create(int initial_size)
{
  Dictionary d;

  if (initial_size < 2) initial_size = 2;
  if (!(d = malloc(sizeof(*d)))) return NULL;
  d->keys = d->values = NULL;
  d->index2seqno = d->seqno2index = NULL;
  if (!(d->keys = malloc(initial_size * sizeof(*(d->keys)))) ||
      !(d->values = malloc(initial_size * sizeof(*(d->values)))) ||
      !(d->seqno2index = malloc(initial_size * sizeof(*(d->seqno2index)))) ||
      !(d->index2seqno = malloc(initial_size * sizeof(*(d->index2seqno))))) {
    free(d->index2seqno);
    free(d->seqno2index);
    free(d->values);
    free(d->keys);
    free(d);
    return NULL;
  }
  d->size = initial_size;
  d->entries = 0;
  return d;
}
