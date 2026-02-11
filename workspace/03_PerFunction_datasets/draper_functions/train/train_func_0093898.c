lane_print(const u_char *p, u_int length, u_int caplen)
{
	struct lane_controlhdr *lec;
	struct lecdatahdr_8023 *ep;
	u_short ether_type;
	u_short extracted_ethertype;

	if (caplen < sizeof(struct lane_controlhdr)) {
		printf("[|lane]");
		return;
	}

	lec = (struct lane_controlhdr *)p;
	if (EXTRACT_16BITS(&lec->lec_header) == 0xff00) {


		printf("lec: proto %x vers %x %s",
		    lec->lec_proto, lec->lec_vers,
		    tok2str(lecop2str, "opcode-#%u", EXTRACT_16BITS(&lec->lec_opcode)));
		return;
	}

	if (caplen < sizeof(struct lecdatahdr_8023)) {
		printf("[|lane]");
		return;
	}

	if (eflag)
		lane_hdr_print(p, length);


	length -= sizeof(struct lecdatahdr_8023);
	caplen -= sizeof(struct lecdatahdr_8023);
	ep = (struct lecdatahdr_8023 *)p;
	p += sizeof(struct lecdatahdr_8023);

	ether_type = EXTRACT_16BITS(&ep->h_type);


	if (ether_type <= ETHERMTU) {

		if (llc_print(p, length, caplen, ep->h_source, ep->h_dest,
		    &extracted_ethertype) == 0) {

			if (!eflag)
				lane_hdr_print((u_char *)ep, length + sizeof(*ep));
			if (extracted_ethertype) {
				printf("(LLC %s) ",
			       etherproto_string(htons(extracted_ethertype)));
			}
			if (!suppress_default_print)
				default_print(p, caplen);
		}
	} else if (ether_encap_print(ether_type, p, length, caplen,
	    &extracted_ethertype) == 0) {

		if (!eflag)
			lane_hdr_print((u_char *)ep, length + sizeof(*ep));
		if (!suppress_default_print)
			default_print(p, caplen);
	}
}
