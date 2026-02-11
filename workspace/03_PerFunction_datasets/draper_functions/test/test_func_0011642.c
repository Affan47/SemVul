store_decimal(const my_decimal *val)
{
  ASSERT_COLUMN_MARKED_FOR_WRITE;
  int err= 0;
  longlong i= convert_decimal2longlong(val, unsigned_flag, &err);
  return test(err | store(i, unsigned_flag));
}
