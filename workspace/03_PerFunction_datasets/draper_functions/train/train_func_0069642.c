gen_fhostop(eaddr, dir)
	register const u_char *eaddr;
	register int dir;
{
	struct block *b0, *b1;

	switch (dir) {
	case Q_SRC:
#ifdef PCAP_FDDIPAD
		return gen_bcmp(OR_LINK, 6 + 1 + pcap_fddipad, 6, eaddr);
#else
		return gen_bcmp(OR_LINK, 6 + 1, 6, eaddr);
#endif

	case Q_DST:
#ifdef PCAP_FDDIPAD
		return gen_bcmp(OR_LINK, 0 + 1 + pcap_fddipad, 6, eaddr);
#else
		return gen_bcmp(OR_LINK, 0 + 1, 6, eaddr);
#endif

	case Q_AND:
		b0 = gen_fhostop(eaddr, Q_SRC);
		b1 = gen_fhostop(eaddr, Q_DST);
		gen_and(b0, b1);
		return b1;

	case Q_DEFAULT:
	case Q_OR:
		b0 = gen_fhostop(eaddr, Q_SRC);
		b1 = gen_fhostop(eaddr, Q_DST);
		gen_or(b0, b1);
		return b1;

	case Q_ADDR1:
		bpf_error("'addr1' is only supported on 802.11");
		break;

	case Q_ADDR2:
		bpf_error("'addr2' is only supported on 802.11");
		break;

	case Q_ADDR3:
		bpf_error("'addr3' is only supported on 802.11");
		break;

	case Q_ADDR4:
		bpf_error("'addr4' is only supported on 802.11");
		break;

	case Q_RA:
		bpf_error("'ra' is only supported on 802.11");
		break;

	case Q_TA:
		bpf_error("'ta' is only supported on 802.11");
		break;
	}
	abort();

}
