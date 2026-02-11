compareTypeListsHelper(const DOH *a, const DOH *b, int opt_equal) {
    List *la = (List *) a;
    List *lb = (List *) b;

    Iterator ia = First(la);
    Iterator ib = First(lb);

    while (ia.item && ib.item) {
      int ret = Strcmp(ia.item, ib.item);
      if (ret)
	return ret;
      ia = Next(Next(ia));
      ib = Next(Next(ib));
    } if (opt_equal && ia.item && Strcmp(ia.item, "^^##optional$$") == 0)
      return 0;
    if (ia.item)
      return -1;
    if (opt_equal && ib.item && Strcmp(ib.item, "^^##optional$$") == 0)
      return 0;
    if (ib.item)
      return 1;

    return 0;
  }
