argus_ether_hostton(char *name)
{
   register struct argus_etherent *ep;
   register u_char *ap;
   static FILE *fp = NULL;
   static int init = 0;

   if (!init) {
      fp = fopen(PCAP_ETHERS_FILE, "r");
      ++init;
      if (fp == NULL)
         return (NULL);
   } else if (fp == NULL)
      return (NULL);
   else
      rewind(fp);

   while ((ep = argus_next_etherent(fp)) != NULL) {
      if (strcmp(ep->name, name) == 0) {
         ap = (u_char *)malloc(6);
         if (ap != NULL) {
            memcpy(ap, ep->addr, 6);
            return (ap);
         }
         break;
      }
   }
   return (NULL);
}
