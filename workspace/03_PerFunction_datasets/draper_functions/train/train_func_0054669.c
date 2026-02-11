getAppcount(appid)
char *appid;
{
   int i, count ;

   for (i = 0, count = 0 ; i < TABLE_SIZE ; i++)
      if ((table[i].used == USED) && (!strcmp(appid, table[i].appid)))
         count++ ;
   return count ;
}
