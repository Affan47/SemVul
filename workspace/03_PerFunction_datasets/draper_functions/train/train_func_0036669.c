gen_linux_sll_linktype(proto)
	register int proto;
{
	struct block *b0, *b1;

	switch (proto) {

	case LLCSAP_ISONS:
	case LLCSAP_IP:
	case LLCSAP_NETBEUI:


		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, LINUX_SLL_P_802_2);
		b1 = gen_cmp(OR_MACPL, 0, BPF_H, (bpf_int32)
			     ((proto << 8) | proto));
		gen_and(b0, b1);
		return b1;

	case LLCSAP_IPX:


		b0 = gen_cmp(OR_MACPL, 0, BPF_B, (bpf_int32)LLCSAP_IPX);
		b1 = gen_snap(0x000000, ETHERTYPE_IPX);
		gen_or(b0, b1);
		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, LINUX_SLL_P_802_2);
		gen_and(b0, b1);


		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, LINUX_SLL_P_802_3);
		gen_or(b0, b1);


		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H,
		    (bpf_int32)ETHERTYPE_IPX);
		gen_or(b0, b1);
		return b1;

	case ETHERTYPE_ATALK:
	case ETHERTYPE_AARP:


		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, LINUX_SLL_P_802_2);


		if (proto == ETHERTYPE_ATALK)
			b1 = gen_snap(0x080007, ETHERTYPE_ATALK);
		else
			b1 = gen_snap(0x000000, ETHERTYPE_AARP);
		gen_and(b0, b1);


		b0 = gen_cmp(OR_LINK, off_linktype, BPF_H, (bpf_int32)proto);

		gen_or(b0, b1);
		return b1;

	default:
		if (proto <= ETHERMTU) {


			b0 = gen_cmp(OR_LINK, off_linktype, BPF_H,
			    LINUX_SLL_P_802_2);
			b1 = gen_cmp(OR_LINK, off_macpl, BPF_B,
			     (bpf_int32)proto);
			gen_and(b0, b1);
			return b1;
		} else {


			return gen_cmp(OR_LINK, off_linktype, BPF_H,
			    (bpf_int32)proto);
		}
	}
}
