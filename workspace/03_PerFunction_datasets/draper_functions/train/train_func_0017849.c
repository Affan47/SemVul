is(char *type) {
  DictEntry *e;

  return (e = find("Type")) && e->val.isName(type);
}
