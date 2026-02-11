match(char *st, int end)
{
   int                 k;
   char               *ptr;

   k = 0;
   ptr = lptr;
   while (st[k])
     {
	if (st[k] != *ptr)
	   return 0;
	k += 1;
	ptr += 1;
     }
   if (end)
     {
	if (alphanum(*ptr))
	   return 0;
     }
   lptr = ptr;
   return 1;
}
