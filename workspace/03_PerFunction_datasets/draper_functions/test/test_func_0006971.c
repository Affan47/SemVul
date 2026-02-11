power_of_two(n)

int               n;


{
         int      i;

         for (i = n; i > 1; i >>= 1)
                  if (i & 1) return FALSE;
         return TRUE;
}
