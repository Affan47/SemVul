Splicestring_gc (List_T *splicestrings, int nsplicesites) {
  int i;
  List_T list, p;
  Splicestring_T splicestring;

  for (i = 0; i < nsplicesites; i++) {
    list = splicestrings[i];
    for (p = list; p != NULL; p = List_next(p)) {
      splicestring = (Splicestring_T) List_head(p);
      Splicestring_free(&splicestring);
    }
    List_free(&list);
  }
  FREE(splicestrings);
  return;
}
