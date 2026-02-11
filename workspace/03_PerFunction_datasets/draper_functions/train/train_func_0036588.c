val_int(void)
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  short j;
#ifdef WORDS_BIGENDIAN
  if (table->s->db_low_byte_first)
    j=sint2korr(ptr);
  else
#endif
    shortget(j,ptr);
  return unsigned_flag ? (longlong) (unsigned short) j : (longlong) j;
}
