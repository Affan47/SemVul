Exclude(const char *prefix,const PatternSet *x)
{
   if(!x)
      return;
   for(int i=0; i<fnum; i++)
   {
      if(do_exclude_match(prefix,files[i],x))
      {
	 Sub(i);
	 i--;
      }
   }
}
