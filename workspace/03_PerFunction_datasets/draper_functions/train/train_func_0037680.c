CmdHelp(ClientInfo *p,ConfClient *pCC,char *Arg)
{
   struct COMMAND_TABLE *pTbl = commandtable;

   if(CustomHelp != NULL) {
      BufPrintf(p,"%s",CustomHelp);
   }
   else {
      BufPrintf(p,"Commands:\r");

      pTbl = commandtable;
      while(pTbl->CmdString != NULL) {
         if(!(pTbl->Flags & CMD_FLAG_NOLIST) &&
            (!(pTbl->Flags & CMD_FLAG_ADMIN) || pCC->bAdmin) &&
            (!(pTbl->Flags & CMD_FLAG_SYSOP) || pCC->bSysop) &&
            (!(pTbl->Flags & CMD_FLAG_SCRIPT) || pCC->bCmdLine) &&
            (!(pTbl->Flags & CMD_FLAG_NOSCRIPT) || !pCC->bCmdLine) &&
            (!(pTbl->Flags & CMD_FLAG_NEED_DISK) || EnableDiskCommands) &&
            (!(pTbl->Flags & CMD_FLAG_LURK) || !bLurkDisabled))
         {
            BufPrintf(p,".%s:\r   %s\r",pTbl->CmdString,pTbl->HelpString);
         }
         pTbl++;
      }
   }
}
