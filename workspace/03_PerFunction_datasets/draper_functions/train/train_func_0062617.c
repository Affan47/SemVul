save_in_field(Field *to, bool no_conversions)
{
  int res;
  DBUG_ASSERT(!result_field);
  res= (*ref)->save_in_field(to, no_conversions);
  null_value= (*ref)->null_value;
  return res;
}
