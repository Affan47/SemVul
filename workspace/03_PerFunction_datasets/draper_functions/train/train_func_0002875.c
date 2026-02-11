operator==(const Path &p2) const
{
   const Path &p1=*this;
   if(p1.is_file!=p2.is_file)
      return false;
   if(xstrcmp(p1.path,p2.path))
      return false;
   if(xstrcmp(p1.url,p2.url))
      return false;
   return true;
}
