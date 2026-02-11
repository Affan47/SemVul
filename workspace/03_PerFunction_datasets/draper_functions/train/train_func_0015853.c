val_int()
{
  DBUG_ASSERT(fixed == 1);
  if ((!value_cached && !cache_value_int()) || null_value)
    return 0;
  return int_value;
}
