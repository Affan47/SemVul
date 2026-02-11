val_int()
{
  DBUG_ASSERT(fixed == 1);
  ulonglong value= (ulonglong) args[0]->val_int();
  if ((null_value= args[0]->null_value))
    return 0;
  return (longlong) my_count_bits(value);
}
