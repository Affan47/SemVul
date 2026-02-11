CreateHostFile(void *Dummy)
{
   struct avl_traverser avl_trans;
   struct hostent *pTemp = NULL;
   HostEntry *pHost;
   IPAdrUnion IPAdr;
   char  TempFilename[80];
   char  HostFilename[80];
   FILE *fp;

   snprintf(HostFilename,sizeof(HostFilename),"%s/%s." HOST_FILENAME_EXT,
            TempDir,AppName);
   snprintf(TempFilename,sizeof(TempFilename),"%s." TEMP_EXT,HostFilename);

   if((fp = fopen(TempFilename,"w")) != NULL) {
      TAKE_MUTEX(&HostMutex);
      pHost = (HostEntry *) avl_t_first(&avl_trans,HostTree);
      GIVE_MUTEX(&HostMutex);

      while(pHost != NULL) {
         pTemp = gethostbyname(pHost->HostName);
         if(pTemp != NULL) {
            IPAdr.ADDR = IP_FROM_HOSTENT(pTemp,0);
            if(IPAdr.ADDR != INADDR_NONE) {
               fprintf(fp,"%s\t%s\n",inet_ntoa(IPAdr.i.sin_addr),
                       pHost->HostName);
               pHost->IPAdr = IPAdr.ADDR;
            }
         }
         TAKE_MUTEX(&HostMutex);
         pHost = (HostEntry *) avl_t_next(&avl_trans);
         GIVE_MUTEX(&HostMutex);
      }
      fclose(fp);
      unlink(HostFilename);
      rename(TempFilename,HostFilename);
   }

#ifdef _WIN32
   bUpdateProcessRunning = FALSE;
   _endthreadex(0);
#endif

   return 0;
}
