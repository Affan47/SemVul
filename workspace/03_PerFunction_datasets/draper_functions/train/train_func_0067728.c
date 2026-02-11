uListIn (ULIST *ul, const void *key, int (*compareFunc)(const void *, const void*)) {
  int i;

  for (i = 0; i < ul->num; ++i) {
    if (!compareFunc(key, &ul->items[i])) {
      return &ul->items[i];
    }
  }
  return NULL;
}
