Hash_str(DOH *ho) {
  int i, j;
  HashNode *n;
  DOH *s;
  static int indent = 4;
  Hash *h = (Hash *) ObjData(ho);

  s = NewStringEmpty();
  if (ObjGetMark(ho)) {
    Printf(s, "Hash(0x%x)", ho);
    return s;
  }
  ObjSetMark(ho, 1);
  Printf(s, "Hash {\n");
  for (i = 0; i < h->hashsize; i++) {
    n = h->hashtable[i];
    while (n) {
      for (j = 0; j < indent; j++)
	Putc(' ', s);
      indent += 4;
      Printf(s, "'%s' : %s, \n", n->key, n->object);
      indent -= 4;
      n = n->next;
    }
  }
  for (j = 0; j < (indent - 4); j++)
    Putc(' ', s);
  Printf(s, "}\n");
  ObjSetMark(ho, 0);
  return s;
}
