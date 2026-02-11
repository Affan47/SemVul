cmp_alignment(const void *a, const void *b) {
  const alignment *x = a;
  const alignment *y = b;
  if (x->score < y->score)
    return +1;
  if (x->score > y->score)
    return -1;

  return strcmp(x->name, y->name);
}
