val_int()
{
  DBUG_ASSERT(fixed == 1);
  store_now_in_TIME(&ltime);
  return (longlong) TIME_to_ulonglong_datetime(&ltime);
}
