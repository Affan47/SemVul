compare_e_string()
{
  String *res1,*res2;
  res1= (*a)->val_str(&value1);
  res2= (*b)->val_str(&value2);
  if (!res1 || !res2)
    return test(res1 == res2);
  return test(sortcmp(res1, res2, cmp_collation.collation) == 0);
}
