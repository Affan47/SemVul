find_command(const char *unprec_name,const char * const *names,
	         const char **res)
{
   const char *match=0;
   for( ; *names; names++)
   {
      const char *s,*u;
      for(s=*names,u=unprec_name; *s && !charcasecmp(*u,*s); s++,u++)
	 ;
      if(*s && !*u)
      {
	 if(match)
	 {
	    *res=0;
	    return 1;
	 }
	 match=*names;
      }
      else if(!*s && !*u)
      {
	 *res=*names;
	 return 1;
      }
   }
   if(match)
   {
      *res=match;
      return 1;
   }
   *res=0;
   return 0;
}
