NextSameSite(FA *scan) const
{
   if(scan==0)
      scan=chain;
   else
      scan=scan->next;
   for( ; scan; scan=scan->next)
      if(scan!=this && SameSiteAs(scan))
	 return scan;
   return 0;
}
