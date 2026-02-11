kill_def(Type1Definition *t1d, int whichd)
{
  if (!t1d)
    return;

  if (whichd < 0)
    for (whichd = dFont; whichd < dLast; whichd = (Dict)(whichd + 1))
      if (dict(whichd, t1d->name()) == t1d)
	break;
  if (whichd < 0 || whichd >= dLast || dict(whichd, t1d->name()) != t1d)
    return;

  int icount = nitems();
  for (int i = first_dict_item(whichd); i < icount; i++)
    if (item(i) == t1d) {
      StringAccum sa;
      sa << '%';
      t1d->gen(sa);
      PermString name = t1d->name();
      Type1CopyItem *t1ci = new Type1CopyItem(sa.take_string());
      set_item(i, t1ci);
      set_dict(whichd, name, 0);
      return;
    }

  assert(0);
}
