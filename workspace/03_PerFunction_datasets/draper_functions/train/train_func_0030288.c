unmapMapid(mapid, protocol)
char *mapid;
u_short protocol;
{
   int i, count ;

   for (i = 0, count = 0 ; i < TABLE_SIZE ; i++)
    {
       if ((table[i].used == USED) && (!strcmp(table[i].mapid, mapid))
	   && (protocol == table[i].protocol))
	{
	   table[i].used = UNUSED ;
	   count = 1 ;
	   break ;
	}
    }
   return count ;
}
