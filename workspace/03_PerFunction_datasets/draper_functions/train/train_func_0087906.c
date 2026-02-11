my_strnncollsp_gbk(CHARSET_INFO * cs __attribute__((unused)),
			      const uchar *a, size_t a_length,
			      const uchar *b, size_t b_length,
                              my_bool diff_if_only_endspace_difference)
{
  size_t length= min(a_length, b_length);
  int res= my_strnncoll_gbk_internal(&a, &b, length);

#ifndef VARCHAR_WITH_DIFF_ENDSPACE_ARE_DIFFERENT_FOR_UNIQUE
  diff_if_only_endspace_difference= 0;
#endif

  if (!res && a_length != b_length)
  {
    const uchar *end;
    int swap= 1;
    if (diff_if_only_endspace_difference)
      res= 1;


    if (a_length < b_length)
    {

      a_length= b_length;
      a= b;
      swap= -1;
      res= -res;
    }
    for (end= a + a_length-length; a < end ; a++)
    {
      if (*a != ' ')
	return (*a < ' ') ? -swap : swap;
    }
  }
  return res;
}
