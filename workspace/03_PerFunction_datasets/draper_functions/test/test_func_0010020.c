gen_p80211_fcdir(int fcdir)
{
	struct block *b0;

	switch (linktype) {

	case DLT_IEEE802_11:
	case DLT_PRISM_HEADER:
	case DLT_IEEE802_11_RADIO_AVS:
	case DLT_IEEE802_11_RADIO:
		break;

	default:
		bpf_error("frame direction supported only with 802.11 headers");

	}

	b0 = gen_mcmp(OR_LINK, 1, BPF_B, (bpf_int32)fcdir,
		(bpf_u_int32)IEEE80211_FC1_DIR_MASK);

	return (b0);
}
