peerForAETitle(const char *AETitle, const char **HostName, int *PortNumber) const
{
   int  i,
    j;

   for(i = 0; i < CNF_Config.noOfAEEntries; i++) {
      for(j = 0; j < CNF_Config.AEEntries[i].noOfPeers; j++) {
         if (!strcmp(AETitle, CNF_Config.AEEntries[i].Peers[j].ApplicationTitle)) {
            *HostName = CNF_Config.AEEntries[i].Peers[j].HostName;
            *PortNumber = CNF_Config.AEEntries[i].Peers[j].PortNumber;
            return(1);
         }
      }
   }

   for(i = 0; i < CNF_HETable.noOfHostEntries; i++) {
      for(j = 0; j < CNF_HETable.HostEntries[i].noOfPeers; j++) {
         if (!strcmp(AETitle, CNF_HETable.HostEntries[i].Peers[j].ApplicationTitle)) {
            *HostName = CNF_HETable.HostEntries[i].Peers[j].HostName;
            *PortNumber = CNF_HETable.HostEntries[i].Peers[j].PortNumber;
            return(2);
         }
      }
   }

   return(0);
}
