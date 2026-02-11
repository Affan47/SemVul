CmdList(ClientInfo *p,ConfClient *pCC,char *Arg)
{
   char *cp;
   char *cp1 = NULL;
   int i;
   Bulletin *pBulletin = BulletinList;

   if((cp = strchr(Arg,' ')) != NULL) {
      *cp++ = 0;
      while(*cp && *cp == ' ') {
         cp++;
      }

      if((cp1 = strchr(cp,' ')) != NULL) {
         *cp1++ = 0;
         while(*cp1 && *cp1 == ' ') {
            cp1++;
         }
      }
   }

   if(pCC->bAdmin && cp != NULL && *cp) {
      if(STRCMP(Arg,"add") == 0) {
         if(cp != NULL && cp1 != NULL) {
            if(CmdListAdd(cp,cp1)) {
               SaveBulletinList();
               BufPrintf(p,"Added: %s as %s\r",cp,cp1);
            }
            else {
               BufPrintf(p,"File \"%s\" not found.\r",cp);
            }
         }
         else {
            BufPrintf(p,"usage: list add <filename> <description>\r");
            Rcode = TBD_ERR_INVALID_CMD;
         }
      }
      else if(STRCMP(Arg,"delete") == 0) {
         if(cp != NULL) {
            CmdBulletinDelete(p,pCC,cp);
         }
         else {
            BufPrintf(p,"usage: list delete <filename>\r");
            Rcode = TBD_ERR_INVALID_CMD;
         }
      }
      else {
         BufPrintf(p,"Usage:\r"
                     "list add <filename> <description>\r"
                     "list delete <filename>\r");
         Rcode = TBD_ERR_INVALID_CMD;
      }
   }
   else {


      i = 1;
      if(pBulletin == NULL) {
         BufPrintf(p,"Sorry, no bulletins are available at this time.\r");
      }
      else {
         BufPrintf(p,"Bulletins:\r");
         while(pBulletin != NULL) {
            if(pCC->bAdmin) {
               BufPrintf(p,"%d. (%s) %s (%s)\r",i++,pBulletin->Filename,
                         pBulletin->Description,pBulletin->RunTime);
            }
            else {
               BufPrintf(p,"%d. %s (%s)\r",i++,pBulletin->Description,
                         pBulletin->RunTime);
            }
            pBulletin = pBulletin->Link;
         }
      }
   }
}
