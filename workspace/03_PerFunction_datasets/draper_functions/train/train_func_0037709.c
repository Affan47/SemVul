compare_date(DATE *a, DATE *b)
{
  bool comp;

  comp = DATE_comp(a, b);

  if (_descent)
    comp = -comp;

  return comp;
}
