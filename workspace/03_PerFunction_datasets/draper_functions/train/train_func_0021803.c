RestoreCWD()
{
   if(cwd_owner==this)
      return 0;
   if(cwd==0)
      return -1;
   const char *err=cwd->Chdir();
   if(!err)
   {
      cwd_owner=this;
      return 0;
   }

   const char *name=cwd->GetName();
   eprintf(_("Warning: chdir(%s) failed: %s\n"),name?name:"?",err);
   return -1;
}
