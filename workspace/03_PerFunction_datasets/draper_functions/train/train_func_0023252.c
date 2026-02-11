add(const FileInfo *info)
{
   if(info->defined&info->TYPE)
   {
      if(dirs_only && info->filetype==info->NORMAL)
	 return;

      if(files_only && info->filetype==info->DIRECTORY)
	 return;
   }

   const char *s=info->name;
   if(s==0)
      return;

   int flags=FNM_PATHNAME;
   if(match_period)
      flags|=FNM_PERIOD;

   if(casefold)
      flags|=FNM_CASEFOLD;

   if(pattern[0]!=0
   && fnmatch(pattern, s, flags)!=0)
      return;

   if(s[0]=='~' && inhibit_tilde)
   {
      char *new_name=alloca_strdup2(s,2);
      strcpy(new_name,"./");
      strcat(new_name,s);
      FileInfo new_info(*info);
      new_info.SetName(new_name);
      add_force(&new_info);
   }
   else
   {
      add_force(info);
   }
}
