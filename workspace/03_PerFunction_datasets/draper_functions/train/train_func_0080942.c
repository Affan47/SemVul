gen_p80211_type(int type, int mask)
{
	struct block *b0;

	switch (linktype) {

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
		b0 = gen_mcmp(OR_LINK, 0, BPF_B, (bpf_int32)type,
		    (bpf_int32)mask);
		break;

	default:
		bpf_error("802.11 link-layer types supported only on 802.11");

	}

	return (b0);
}
