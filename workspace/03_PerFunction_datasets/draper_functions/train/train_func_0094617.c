RaRmonArgusRecord (struct ArgusRecord *argus)
{
   struct ArgusRecord *retn = NULL;
   struct ArgusMeter meter;
   struct ArgusFlow *flow1, *flow2;
   struct ArgusFarHeaderStruct *a1farhdr[32], *a2farhdr[32];
   unsigned int a1DSRStatus = 0, a2DSRStatus = 0;


   if (RaPrintMACAddress)
      if (!(RaCreateEtherFlow (argus)))
         return (retn);

   if ((retn = RaCopyArgusRecord (argus)) != NULL) {

      a1DSRStatus = ArgusIndexRecord (argus, a1farhdr);
      a2DSRStatus = ArgusIndexRecord (retn,  a2farhdr);

      flow1 = &argus->argus_far.flow;
      flow2 = &retn->argus_far.flow;

      switch (argus->ahdr.status & 0xFFFF) {
         case ETHERTYPE_IP:
            flow2->ip_flow.ip_src = flow1->ip_flow.ip_dst;
            flow2->ip_flow.ip_dst = flow1->ip_flow.ip_src;

            switch (flow1->ip_flow.ip_p) {
               case IPPROTO_UDP:
               case IPPROTO_TCP:
                  break;
            }

            meter = argus->argus_far.src;
            argus->argus_far.src = argus->argus_far.dst;
            argus->argus_far.dst = meter;

            break;

         case ETHERTYPE_ARP:
         case ETHERTYPE_REVARP:
            break;

         default:
            bcopy ((char *)&flow1->mac_flow.ehdr.ether_dhost,
                   (char *)&flow2->mac_flow.ehdr.ether_shost, 6);
            bzero ((char *)&flow1->mac_flow.ehdr.ether_dhost, 6);
            bzero ((char *)&flow2->mac_flow.ehdr.ether_dhost, 6);

            meter = retn->argus_far.src;
            retn->argus_far.src = retn->argus_far.dst;
            retn->argus_far.dst = meter;
            break;
      }

      if ((a1DSRStatus & ARGUS_MAC_DSR_STATUS) && (a2DSRStatus & ARGUS_MAC_DSR_STATUS)) {
         struct ArgusMacStruct *mac1 = NULL, *mac2 = NULL;

         mac1 = (struct ArgusMacStruct *) a1farhdr[ARGUS_MAC_DSR_INDEX];
         mac2 = (struct ArgusMacStruct *) a2farhdr[ARGUS_MAC_DSR_INDEX];

         bcopy ((char *)&mac2->ether_mac.etherdst, (char *)&mac1->ether_mac.ethersrc, 6);

         bzero ((char *)&mac1->ether_mac.etherdst, 6);
         bzero ((char *)&mac2->ether_mac.etherdst, 6);
      }

       retn->ahdr.type |= ARGUS_RMON;
      argus->ahdr.type |= ARGUS_RMON;
   }

   return (retn);
}
