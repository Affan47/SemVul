str_result(String *str)
{
  DBUG_ASSERT(fixed == 1);
  check(TRUE);
  update();
  return entry->val_str(&null_value, str, decimals);
}
