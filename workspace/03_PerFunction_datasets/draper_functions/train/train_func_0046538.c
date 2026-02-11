compare_bin(uchar *a, uint a_length, uchar *b, uint b_length,
                       my_bool part_key, my_bool skip_end_space)
{
  uint length= min(a_length,b_length);
  uchar *end= a+ length;
  int flag;

  while (a < end)
    if ((flag= (int) *a++ - (int) *b++))
      return flag;
  if (part_key && b_length < a_length)
    return 0;
  if (skip_end_space && a_length != b_length)
  {
    int swap= 1;


    if (a_length < b_length)
    {

      a_length= b_length;
      a= b;
      swap= -1;
    }
    for (end= a + a_length-length; a < end ; a++)
    {
      if (*a != ' ')
	return (*a < ' ') ? -swap : swap;
    }
    return 0;
  }
  return (int) (a_length-b_length);
}
