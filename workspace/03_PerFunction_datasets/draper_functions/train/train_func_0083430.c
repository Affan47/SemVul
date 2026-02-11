string_cmp(const void* pa, const void* pb){
  const jv* a = pa;
  const jv* b = pb;
  int lena = jv_string_length_bytes(jv_copy(*a));
  int lenb = jv_string_length_bytes(jv_copy(*b));
  int minlen = lena < lenb ? lena : lenb;
  int r = memcmp(jv_string_value(*a), jv_string_value(*b), minlen);
  if (r == 0) r = lena - lenb;
  return r;
}
