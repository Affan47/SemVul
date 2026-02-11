my_strnncoll_gbk_internal(const uchar **a_res, const uchar **b_res,
			      size_t length)
{
  const uchar *a= *a_res, *b= *b_res;
  uint a_char,b_char;

  while (length--)
  {
    if ((length > 0) && isgbkcode(*a,*(a+1)) && isgbkcode(*b, *(b+1)))
    {
      a_char= gbkcode(*a,*(a+1));
      b_char= gbkcode(*b,*(b+1));
      if (a_char != b_char)
        return ((int) gbksortorder((uint16) a_char) -
		(int) gbksortorder((uint16) b_char));
      a+= 2;
      b+= 2;
      length--;
    }
    else if (sort_order_gbk[*a++] != sort_order_gbk[*b++])
      return ((int) sort_order_gbk[a[-1]] -
	      (int) sort_order_gbk[b[-1]]);
  }
  *a_res= a;
  *b_res= b;
  return 0;
}
