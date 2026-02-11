bt_if_print(const struct pcap_pkthdr *h, const u_char *p)
{
	u_int length = h->len;
	u_int caplen = h->caplen;
	const pcap_bluetooth_h4_header* hdr = (const pcap_bluetooth_h4_header*)p;

	if (caplen < BT_HDRLEN) {
		printf("[|bt]");
		return (BT_HDRLEN);
	}
	caplen -= BT_HDRLEN;
	length -= BT_HDRLEN;
	p += BT_HDRLEN;
	if (eflag)
		(void)printf("hci length %d, direction %s, ", length, (EXTRACT_32BITS(&hdr->direction)&0x1)?"in":"out");

	if (!suppress_default_print)
		default_print(p, caplen);

	return (BT_HDRLEN);
}
