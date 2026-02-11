_ht_lower_strcmp(const char *node_key, const char *look_key)
{
  int cn;
  int cl;
  do {
    cn = *node_key++;
    cl = *look_key++;
  } while(cn && cn==tolower(cl));
  return cn - tolower(cl);
}
