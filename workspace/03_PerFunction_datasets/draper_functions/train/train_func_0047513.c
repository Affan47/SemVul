SameLocationAs(const FileAccess *fa) const
{
   if(!SameSiteAs(fa))
      return false;
   SFtp *o=(SFtp*)fa;
   if(xstrcmp(cwd,o->cwd))
      return false;
   if(xstrcmp(home,o->home))
      return false;
   return true;
}
