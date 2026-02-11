HandleListInfoCreation(const FileAccessRef& session,Ref<ListInfo>& list_info,const char *relative_dir)
{
   if(state!=GETTING_LIST_INFO)
      return;

   if(session==target_session && no_target_dir)
   {
      target_set=new FileSet();
      return;
   }

   list_info=session->MakeListInfo();
   if(list_info==0)
   {
      eprintf(_("mirror: protocol `%s' is not suitable for mirror\n"),
	       session->GetProto());
      transfer_count-=root_transfer_count;
      set_state(FINISHING);
      return;
   }
   list_info->UseCache(use_cache);
   int need=FileInfo::ALL_INFO;
   if(flags&IGNORE_TIME)
      need&=~FileInfo::DATE;
   if(flags&IGNORE_SIZE)
      need&=~FileInfo::SIZE;
   list_info->Need(need);
   if(flags&RETR_SYMLINKS)
      list_info->FollowSymlinks();

   list_info->SetExclude(relative_dir,exclude);
   list_info->Roll();
}
