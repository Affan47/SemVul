nextop(int *opidx, int *list)
{
   *opidx = 0;
   while (*list)
     {
	if (matchtoken(*list))
	  {
	     return TRUE;
	  }
	else
	  {
	     list += 1;
	     *opidx += 1;
	  }
     }
   return FALSE;
}
