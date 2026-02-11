nubList(ls)
List ls; {
  List res = NIL;

  while (nonNull(ls)) {
    if (!cellIsMember(hd(ls),res)) {
      res = cons(hd(ls),res);
    }
    ls = tl(ls);
  }
  return res;
}
