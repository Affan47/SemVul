CmdAbout(ClientInfo *p,ConfClient *pCC1,char *Arg)
{
   ConfClient *pCC;
   struct avl_traverser avl_trans;
   ConfServer *pCS = (ConfServer *) p->p;

   pCC = (ConfClient *) avl_t_first(&avl_trans,pCS->ConfTree);
   while(pCC != NULL) {
      if(STRCMP(Arg,pCC->Callsign) == 0) {
         if(pCC->Info != NULL) {
            BufPrintf(p,"\rAbout %s:%s",pCC->Callsign,pCC->Info);
         }
         else {
            BufPrintf(p,"Sorry I don't know anything about %s.\r",Arg);
            Rcode = TBD_STATION_NO_INFO;
         }
         break;
      }
      pCC = (ConfClient *) avl_t_next(&avl_trans);
   }

   if(pCC == NULL) {
      BufPrintf(p,"%s not found\r",Arg);
      Rcode = TBD_STATION_NOT_FOUND;
   }
}
