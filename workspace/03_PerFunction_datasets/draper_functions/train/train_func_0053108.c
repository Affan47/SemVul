Query(const char *closure) const
{
   const char *v=0;

   if(closure)
      v=ResMgr::SimpleQuery(this,closure);
   if(!v)
      v=ResMgr::SimpleQuery(this,0);
   if(!v)
      v=defvalue;

   return v;
}
