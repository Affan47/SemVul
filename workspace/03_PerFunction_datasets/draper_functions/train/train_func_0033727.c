luaH_getstr (Table *t, TString *key) {
  Node *n = hashstr(t, key);
  do {
    if (ttisstring(gkey(n)) && rawtsvalue(gkey(n)) == key)
      return gval(n);
    else n = gnext(n);
  } while (n);
  return luaO_nilobject;
}
