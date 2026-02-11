ilist_subtract(Ilist p1, Ilist p2)
{
  if (p1 == NULL)
    return NULL;
  else {
    Ilist r = ilist_subtract(p1->next, p2);
    if (ilist_member(p2, p1->i))
      return r;
    else
      return ilist_prepend(r, p1->i);
  }
}
