array_free_data(array *a, void (func)(void **d)) {
  int i;
  for(i = 0; i < a->n; i++) {
    func(&(a->data[i]));
  }
  a = array_clear(a);
}
