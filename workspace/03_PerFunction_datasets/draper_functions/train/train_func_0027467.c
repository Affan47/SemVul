stack_destroy(stack *s) {
  while(s->size) {
    s->size--;
  }
  free(s->counts);
  free(s->chars);
  free(s);
}
