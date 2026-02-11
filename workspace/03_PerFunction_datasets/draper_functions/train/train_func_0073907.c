val_real(void)
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  int tmp= unsigned_flag ? (int) ptr[0] :
    (int) ((signed char*) ptr)[0];
  return (double) tmp;
}
