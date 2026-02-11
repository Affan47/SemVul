getnextippkt()
{
  struct pcap_pkthdr useless;
  u_char * packet;

  if (NULL == pcap_global_descriptor) {
    fprintf(stderr, "[pcap] Can't read non-opened pcap descriptor");
  }

  for (;;) {
    packet = (u_char *) pcap_next(pcap_global_descriptor, &useless);
    if (NULL == packet)
      continue;
    packet = packet + offset;

    if ( ((struct ip *) packet)->ip_hl < 5 || ((struct ip *) packet)->ip_v != 4 || iphdr_chksum(packet, ((struct ip *) packet)->ip_hl) != 0 ) {

      continue;
    }


    if (SigHup) {
      struct AllLogsType *pTempLog;
      for (pTempLog = pAllLogs; pTempLog; pTempLog = pTempLog->Next) {
	data_dump(pTempLog);
	data_clear(pTempLog);
      }

      Clean();
      ReInit();
      SigHup = 0;
    }


    if (SigDump) {
      struct AllLogsType * pTempLog;
      for (pTempLog = pAllLogs; pTempLog; pTempLog = pTempLog->Next) {
	data_dump(pTempLog);
      }
      SigDump = 0;
    }
    break;
  }
  return (packet);
}
