C_find_symbol(C_word str, C_SYMBOL_TABLE *stable)
{
  char *sptr = C_c_string(str);
  int
    len = C_header_size(str),
    key = hash_string(len, sptr, stable->size, stable->rand, 0);
  C_word s;

  if(C_truep(s = lookup(key, len, sptr, stable))) return s;
  else return C_SCHEME_FALSE;
}
