rend_id_is_in_interval(const char *a, const char *b, const char *c)
{
  int a_b, b_c, c_a;
  tor_assert(a);
  tor_assert(b);
  tor_assert(c);


  a_b = tor_memcmp(a,b,DIGEST_LEN);
  if (a_b == 0)
    return 0;
  b_c = tor_memcmp(b,c,DIGEST_LEN);
  if (b_c == 0)
    return 0;
  else if (a_b <= 0 && b_c < 0)
    return 0;
  c_a = tor_memcmp(c,a,DIGEST_LEN);
  if (c_a < 0 && a_b <= 0)
    return 0;
  else if (b_c < 0 && c_a < 0)
    return 0;


  return 1;
}
