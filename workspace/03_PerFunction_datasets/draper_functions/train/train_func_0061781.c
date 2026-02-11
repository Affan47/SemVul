badchar_compute(guint8 *pattern, int m,  int *bad)
{
   int i;
   for (i=0;i<256;i++)
       bad[i] = m;

   for (i = 0; i < m - 1; ++i)
       bad[(int)pattern[i]] = m - i - 1;
}
