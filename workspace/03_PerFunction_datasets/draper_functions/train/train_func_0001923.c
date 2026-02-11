gen_eth_init(char *device)
{
   char pcap_errbuf[PCAP_ERRBUF_SIZE];
   pcap_t *p;

#ifndef CYGWIN
   if (!(p = pcap_open_live(device,2048,TRUE,10,pcap_errbuf)))
      goto pcap_error;

   pcap_setdirection(p,PCAP_D_INOUT);
#ifdef BIOCFEEDBACK
   {
     int on = 1;
     ioctl(pcap_fileno(p), BIOCFEEDBACK, &on);
   }
#endif
#else
   p = pcap_open(device,2048,
                 PCAP_OPENFLAG_PROMISCUOUS |
                 PCAP_OPENFLAG_NOCAPTURE_LOCAL |
		 PCAP_OPENFLAG_MAX_RESPONSIVENESS |
		 PCAP_OPENFLAG_NOCAPTURE_RPCAP,
		 10,NULL,pcap_errbuf);

   if (!p)
      goto pcap_error;
#endif

   return p;

 pcap_error:
   fprintf(stderr,"gen_eth_init: unable to open device '%s' "
           "with PCAP (%s)\n",device,pcap_errbuf);
   return NULL;
}
