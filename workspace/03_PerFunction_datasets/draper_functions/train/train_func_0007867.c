checkForSameVendor(const char *AETitle1, const char *AETitle2) const
{
   int  i,
    j,
    k,
    found = 0;

   for(i = 0; i < CNF_VendorTable.noOfHostEntries; i++) {
      for(j = 0; j < CNF_VendorTable.HostEntries[i].noOfPeers; j++) {
         if (!strcmp(AETitle1, CNF_VendorTable.HostEntries[i].Peers[j].ApplicationTitle)) {
            for(k = 0; k < CNF_VendorTable.HostEntries[i].noOfPeers; k++) {
               if (!strcmp(AETitle2, CNF_VendorTable.HostEntries[i].Peers[k].ApplicationTitle))
                  found = 1;
            }
         }
      }
   }

   return(found);
}
