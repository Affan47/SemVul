array_insert_p(array *a, void **data, int where) {
  int n;
  if(where <= 0) {
    where = 0;
  }
  if(where >= a->n) {
    where = a->n;
  }

  a = array_check(a);
  n = a->n + 1;
  if(n >= a->alloc) {
    array_grow(a, n);
  }

  array_slide_down(a, where);
  a->data[where] = *data;
  a->n = n;

  return(a);
}
