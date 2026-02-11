get_east8_2(char *ptr, const int col, const int iw,
                 const int failcode)
{
   if (col >= iw-1)
      return failcode;

      return *(ptr+ 1);
}
