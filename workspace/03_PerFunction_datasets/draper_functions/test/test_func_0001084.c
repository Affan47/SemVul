ArgusUpdateArpState (struct ArgusFlowStruct *flowstr, unsigned char *state)
{
   struct ether_arp *arp = (struct ether_arp *)(ArgusThisEpHdr + 1);
   struct ArgusARPObject *arpobj = NULL;

   ArgusTallyTime (flowstr, *state);

   if (STRUCTCAPTURED(*arp)) {
      ArgusThisLength -= sizeof(*arp);
      ArgusSnapLength -= sizeof(*arp);
      ArgusThisUpHdr = (unsigned char *)(arp + 1);

      ArgusUpdateAppState (flowstr, state);

      if (*state == ARGUS_START) {
         if (flowstr->NetworkDSRBuffer != NULL)
            ArgusFree(flowstr->NetworkDSRBuffer);

         if ((arpobj = (void *) ArgusCalloc (1, sizeof(struct ArgusARPObject))) == NULL)
            ArgusLog (LOG_ERR, "ArgusNewFlow: ArgusCalloc %s", strerror(errno));
         else
            flowstr->NetworkDSRBuffer = (void *) arpobj;
      } else
         arpobj = (void *) flowstr->NetworkDSRBuffer;

      switch (arp->arp_op) {
         case ARPOP_REQUEST:
            ArgusInProtocol = 0;
            break;

         case ARPOP_REPLY:
            bcopy ((unsigned char *)&SHA(arp), arpobj->respaddr, 6);
            break;
      }
   }
}
