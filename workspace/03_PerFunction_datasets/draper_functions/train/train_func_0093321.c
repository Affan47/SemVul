arcnet_linux_if_print(const struct pcap_pkthdr *h, const u_char *p)
{
	u_int caplen = h->caplen;
	u_int length = h->len;
	const struct arc_linux_header *ap;

	int archdrlen = 0;
	u_char arc_type;

	if (caplen < ARC_LINUX_HDRLEN) {
		printf("[|arcnet]");
		return (caplen);
	}

	ap = (const struct arc_linux_header *)p;
	arc_type = ap->arc_type;

	switch (arc_type) {
	default:
		archdrlen = ARC_LINUX_HDRNEWLEN;
		if (caplen < ARC_LINUX_HDRNEWLEN) {
			printf("[|arcnet]");
			return (caplen);
		}
		break;
	case ARCTYPE_IP_OLD:
	case ARCTYPE_ARP_OLD:
	case ARCTYPE_DIAGNOSE:
		archdrlen = ARC_LINUX_HDRLEN;
		break;
	}

	if (eflag)
		arcnet_print(p, length, 0, 0, 0);


	length -= archdrlen;
	caplen -= archdrlen;
	p += archdrlen;

	if (!arcnet_encap_print(arc_type, p, length, caplen))
		default_print(p, caplen);

	return (archdrlen);
}
