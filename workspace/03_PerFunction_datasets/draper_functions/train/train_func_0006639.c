builtin_cd()
{
   if(args->count()==1)
      args->Append("~");

   bool is_file=false;

   if(args->count()!=2)
   {

      eprintf(_("Usage: cd remote-dir\n"));
      return 0;
   }

   const char *dir=args->getarg(1);
   const char *url=0;

   if(!strcmp(dir,"-"))
   {
      dir=cwd_history.Lookup(session);
      if(!dir)
      {
	 eprintf(_("%s: no old directory for this site\n"),args->a0());
	 return 0;
      }
      args->setarg(1,dir);
      dir=args->getarg(1);
   }

   bool dir_needs_slash=false;
   if(url::is_url(dir))
   {
      ParsedURL u(dir,true);
      FileAccess *new_session=FileAccess::New(&u);
      bool same_site=session->SameSiteAs(new_session);
      Delete(new_session);
      if(!same_site)
	 return builtin_open();
      url=dir;
      dir=alloca_strdup(u.path);
      dir_needs_slash=url::dir_needs_trailing_slash(u.proto);
   }
   else
   {
      dir_needs_slash=url::dir_needs_trailing_slash(session->GetProto());
   }

   if(dir_needs_slash)
      is_file=(last_char(dir)!='/');

   int cache_is_dir=FileAccess::cache->IsDirectory(session,dir);
   if(cache_is_dir==1)
   {
      if(is_file && dir_needs_slash)
	 dir=xstring::get_tmp(dir).append('/');
      is_file=false;
   }
   else if(cache_is_dir==0)
      is_file=true;

   old_cwd=session->GetCwd();
   FileAccess::Path new_cwd(old_cwd);
   new_cwd.Change(dir,is_file);
   if(url)
      new_cwd.SetURL(url);
   if(!verify_path || background
   || (!verify_path_cached && cache_is_dir==1))
   {
      cwd_history.Set(session,old_cwd);
      session->SetCwd(new_cwd);
      if(slot)
	 ConnectionSlot::SetCwd(slot,new_cwd);
      exit_code=0;
      return 0;
   }
   session->PathVerify(new_cwd);
   session->Roll();
   builtin=BUILTIN_CD;
   return this;
}
