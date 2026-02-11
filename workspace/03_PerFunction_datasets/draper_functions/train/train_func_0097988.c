get(const std::string key, int&value) {
  t_atom*a=get(key);
  if(a && A_FLOAT==a->a_type) {
    value=atom_getint(a);
  }
}
