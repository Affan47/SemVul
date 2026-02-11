re_match(const char *line,const char *a,int flags)
{
   if(!a || !*a)
      return false;
   regex_t re;
   if(regcomp(&re,a,REG_EXTENDED|REG_NOSUB|flags))
      return false;
   bool res=(0==regexec(&re,line,0,0,0));
   regfree(&re);
   return res;
}
