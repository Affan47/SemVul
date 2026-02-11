val_bool_result()
{
  DBUG_ASSERT(fixed == 1);
  check(TRUE);
  update();
  return entry->val_int(&null_value) != 0;
}
