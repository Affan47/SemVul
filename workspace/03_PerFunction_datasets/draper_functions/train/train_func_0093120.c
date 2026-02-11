cmp(const uchar *a_ptr, const uchar *b_ptr)
{
  signed char a,b;
  a=(signed char) a_ptr[0]; b= (signed char) b_ptr[0];
  if (unsigned_flag)
    return ((uchar) a < (uchar) b) ? -1 : ((uchar) a > (uchar) b) ? 1 : 0;
  return (a < b) ? -1 : (a > b) ? 1 : 0;
}
