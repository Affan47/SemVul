FormatPrompt(const char *scan)
{
   const char *cwd=session->GetCwd();
   if(cwd==0 || cwd[0]==0)
      cwd="~";
   {
      const char *home=session->GetHome();
      if(home && strcmp(home,"/") && !strncmp(cwd,home,strlen(home))
      && (cwd[strlen(home)]=='/' || cwd[strlen(home)]==0))
      {
	 cwd=xstring::format("~%s",cwd+strlen(home));
      }
   }
   const char *cwdb=session->GetCwd();
   cwdb=session->GetCwd();
   if(cwdb==0 || cwdb[0]==0)
      cwdb="~";
   const char *p=strrchr(cwdb,'/');
   if(p && p>cwdb)
      cwdb=p+1;

   static const char StartIgn[]={RL_PROMPT_START_IGNORE,0};
   static const char EndIgn[]={RL_PROMPT_END_IGNORE,0};

   subst_t subst[] = {
      { 'a', "\007" },
      { 'e', "\033" },
      { 'n', "\n" },
      { 's', "lftp" },
      { 'v', VERSION },

      { 'h', session->GetHostName() },
      { 'u', session->GetUser() },

      { '@', session->GetUser()?"@":"" },
      { 'U', session->GetConnectURL() },
      { 'S', slot?slot.get():"" },
      { 'w', cwd },
      { 'W', cwdb },
      { '[', StartIgn },
      { ']', EndIgn },
      { 0, "" }
   };
   static xstring_c prompt;
   prompt.set_allocated(Subst(scan, subst));

   return(prompt);
}
