string_equal(string *a, string *b) {
  if(a == NULL      || b == NULL      ||
     a->str == NULL || b->str == NULL) {
    return 0;
  }
  return( strcmp(a->str, b->str) == 0 );
}
