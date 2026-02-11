RaSortDstTos (struct ArgusRecord *a1, struct ArgusRecord *a2)
{
   int retn = 0;

   if ((a1->ahdr.status & 0xFFFF) == ETHERTYPE_IP)
      retn =  (a2->argus_far.attr_ip.dtos - a1->argus_far.attr_ip.dtos);

   return (retn);
}
