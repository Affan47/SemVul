unmapPid(pid)
u_long pid;
{
   int i, count ;

   for (i = 0, count = 0 ; i < TABLE_SIZE ; i++)
    {
       if ((table[i].used == USED) && (table[i].pid == pid))
	{
	   table[i].used = UNUSED ;
	   count++ ;
	}
    }
   return count ;
}
