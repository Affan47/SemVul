galois_get_mult_table(int w)
{
  if (galois_mult_tables[w] == NULL) {
    if (galois_create_mult_tables(w)) {
      return NULL;
    }
  }
  return galois_mult_tables[w];
}
