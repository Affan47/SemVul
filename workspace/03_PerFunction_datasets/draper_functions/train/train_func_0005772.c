print_packet(struct pkt *npkt) {
	time_t seconds;
	struct pkt tpkt;
	char buf[128];
	uint64_t reftime, org, rec, xmt;

	memcpy(&reftime, &npkt->reftime, sizeof(uint64_t));
	memcpy(&org, &npkt->org, sizeof(uint64_t));
	memcpy(&rec, &npkt->rec, sizeof(uint64_t));
	memcpy(&xmt, &npkt->xmt, sizeof(uint64_t));

	printf("li_vn_mode           : %02d / LI: %d, VN: %d, MODE : %d\n", (uint8_t)npkt->li_vn_mode, npkt->li_vn_mode >> 6,
															((npkt->li_vn_mode >> 3) & 0x7), npkt->li_vn_mode & 0x7);
	printf("Stratum              : %02d\n", npkt->stratum);
	printf("Poll                 : %02d\n", npkt->ppoll);
	printf("Precision            : %02d\n", npkt->precision);
	printf("Root Delay           : %02x\n", npkt->rootdelay);
	printf("Root Dispersion      : %02x\n", npkt->rootdispersion);
	printf("Reference Identifier : %02x\n", npkt->refid);
	printf("Reference Timestamp  : %02lx\n", reftime);
	printf("Originate Timestamp  : %02lx\n", org);
	printf("Receive Timestamp    : %02lx\n", rec);
	printf("Transmit Timestamp   : %02lx\n", xmt);

	NTOHL_FP(&npkt->reftime, &tpkt.reftime);
	NTOHL_FP(&npkt->org, &tpkt.org);
	NTOHL_FP(&npkt->rec, &tpkt.rec);
	NTOHL_FP(&npkt->xmt, &tpkt.xmt);

	NTP_TO_UNIX(tpkt.reftime.l_ui, seconds);
	strftime(buf, sizeof(buf), "%Y/%m/%d %T",localtime(&seconds));
	printf("Reference Time       : %s\n", buf);

	NTP_TO_UNIX(tpkt.org.l_ui, seconds);
	strftime(buf, sizeof(buf), "%Y/%m/%d %T",localtime(&seconds));
	printf("Originate Time       : %s\n", buf);

	NTP_TO_UNIX(tpkt.rec.l_ui, seconds);
	strftime(buf, sizeof(buf), "%Y/%m/%d %T",localtime(&seconds));
	printf("Receive Time         : %s\n", buf);

	NTP_TO_UNIX(tpkt.xmt.l_ui, seconds);
	strftime(buf, sizeof(buf), "%Y/%m/%d %T",localtime(&seconds));
	printf("Transmit Time        : %s\n", buf);
}
