fc_strlcpy(char *dest, const char *src, size_t n)
{
  fc_assert_ret_val(NULL != dest, -1);
  fc_assert_ret_val(NULL != src, -1);
  fc_assert_ret_val(0 < n, -1);
#ifdef HAVE_STRLCPY
  return strlcpy(dest, src, n);
#else
  {
    size_t len = strlen(src);
    size_t num_to_copy = (len >= n) ? n-1 : len;
    if (num_to_copy>0)
      memcpy(dest, src, num_to_copy);
    dest[num_to_copy] = '\0';
    return len;
  }
#endif
}
