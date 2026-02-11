PushDirState(char *name,struct stat *sb)

{
if (chdir(name) == -1)
   {
   CfOut(cf_inform,"chdir","Could not change to directory %s, mode %o in tidy",name,sb->st_mode & 07777);
   return false;
   }
else
   {
   Debug("Changed directory to %s\n",name);
   }

CheckLinkSecurity(sb,name);
return true;
}
