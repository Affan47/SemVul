ServerConnectionReady(char *server)

{ struct Rlist *rp;
  struct ServerItem *svp;
  char ipname[CF_MAXVARSIZE];

ThreadLock(cft_getaddr);
strncpy(ipname,Hostname2IPString(server),CF_MAXVARSIZE-1);
ThreadUnlock(cft_getaddr);

for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   svp = (struct ServerItem *)rp->item;

   if (svp == NULL)
      {
      continue;
      }

   if (svp->busy)
      {
      CfOut(cf_verbose,"","Existing connection to %s seems to be active...\n",ipname);
      return NULL;
      }

   if ((strcmp(ipname,svp->server) == 0) && svp->conn && svp->conn->sd > 0)
      {
      CfOut(cf_verbose,"","Connection to %s is already open and ready...\n",ipname);
      svp->busy = true;
      return svp->conn;
      }
   }

CfOut(cf_verbose,"","No existing connection to %s is established...\n",ipname);
return NULL;
}
