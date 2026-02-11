select_only(void* l, int docallbacks) {
  if (!l) return deselect(docallbacks);
  int change = 0;
  if (type() == FL_MULTI_BROWSER) {
    for (void* p = item_first(); p; p = item_next(p))
      if (p != l) change |= select(p, 0, docallbacks);
  }
  change |= select(l, 1, docallbacks);
  display(l);
  return change;
}
