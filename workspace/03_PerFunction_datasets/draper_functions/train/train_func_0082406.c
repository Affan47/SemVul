strn_copy_to_upper(apr_pool_t *pool, const char *str, apr_size_t n) {
  int i = 0;
  unsigned char *tmp = apr_pcalloc(pool, n + 1);

  while (str && str[i] && i < n) {
    tmp[i] = apr_toupper(str[i]);
    ++i;
  }

  return tmp;
}
