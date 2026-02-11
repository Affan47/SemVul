Find(const char *alias)
{
   Alias *scan=base;
   while(scan)
   {
      int dif=strcasecmp(scan->alias,alias);
      if(dif==0)
	 return(scan->value);
      if(dif>0)
	 break;
      scan=scan->next;
   }
   return 0;
}
