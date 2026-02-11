cli_fetch_lengths(ulong *to, MYSQL_ROW column,
			      unsigned int field_count)
{
  ulong *prev_length;
  char *start=0;
  MYSQL_ROW end;

  prev_length=0;
  for (end=column + field_count + 1 ; column != end ; column++, to++)
  {
    if (!*column)
    {
      *to= 0;
      continue;
    }
    if (start)
      *prev_length= (ulong) (*column-start-1);
    start= *column;
    prev_length= to;
  }
}
