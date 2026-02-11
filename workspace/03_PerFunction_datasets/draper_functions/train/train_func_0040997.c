val_real(void)
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  long j= unsigned_flag ? (long) uint3korr(ptr) : sint3korr(ptr);
  return (double) j;
}
