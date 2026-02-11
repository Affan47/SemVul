CENUM_get_next(CENUM *cenum)
{
  if (!cenum)
    return _enum_list;
  else
    return cenum->list.next;
}
