set_error(const char *s1,const char *s2)
{
   if(s2)
      error.vset(s1,": ",s2,NULL);
   else
      error.set(s1);
}
