CmdAdmin(ClientInfo *p,ConfClient *pCC,char *Arg)
{
   if(AdminPass != NULL && STRCMP(AdminPass,Arg) == 0) {
      pCC->bAdmin = TRUE;
      pCC->bSysop = TRUE;
      pCC->bMuted = FALSE;
      BufPrintf(p,"Your wish is my command.\r");
      LOG_NORM(("Admin %s logged in\n",pCC->Callsign));
   }
}
