RaSortSrcAddr (struct ArgusRecord *a2, struct ArgusRecord *a1)
{
  int retn = 0;

   if ((retn = (a1->ahdr.status & 0xFFFF) - (a2->ahdr.status & 0xFFFF)) == 0) {
      switch (a1->ahdr.status & 0xFFFF) {
         case ETHERTYPE_IP: {
            unsigned int addr1 = a1->argus_far.flow.ip_flow.ip_src;
            unsigned int addr2 = a2->argus_far.flow.ip_flow.ip_src;
            retn = (addr1 > addr2) ? 1 : ((addr1 == addr2) ? 0 : -1);
            break;
         }

         case ETHERTYPE_ARP: {
            unsigned int addr1 = a1->argus_far.flow.arp_flow.arp_spa;
            unsigned int addr2 = a2->argus_far.flow.arp_flow.arp_spa;
            retn = (addr1 > addr2) ? 1 : ((addr1 == addr2) ? 0 : -1);
            break;
         }

         default:
            retn = bcmp ((char *)&a2->argus_far.flow.mac_flow.ehdr.ether_shost, (char *)&a1->argus_far.flow.mac_flow.ehdr.ether_shost, 6);
            break;
      }
   }

   return (retn);
}
