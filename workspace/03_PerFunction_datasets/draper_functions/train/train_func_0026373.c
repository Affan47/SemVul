val_real(void)
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  int not_used;
  char *end_not_used;
  return my_strntod(&my_charset_bin, (char*) ptr, field_length, &end_not_used,
                    &not_used);
}
