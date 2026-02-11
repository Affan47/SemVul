bt_defcmp(const DBT *a, const DBT *b) {
  size_t len;
  uint8_t *p1, *p2;


  len = std::min(a->size, b->size);
  for (p1 = (uint8_t *)a->data, p2 = (uint8_t *)b->data; len--; ++p1, ++p2)
    if (*p1 != *p2) return ((int)*p1 - (int)*p2);
  return ((int)a->size - (int)b->size);
}
