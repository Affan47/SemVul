inthash_read_value(inthash hashtable, const char *name,
                       inthash_value * pvalue) {
  inthash_value* const value = inthash_read_value_(hashtable, name);
  if (value != NULL) {
    if (pvalue != NULL) {
      *pvalue = *value;
    }
    return 1;
  }
  return 0;
}
