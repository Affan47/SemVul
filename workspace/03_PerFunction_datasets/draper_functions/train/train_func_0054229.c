hfi1_filter_ibpacket_type(void *ibhdr, void *packet_data,
				     void *value)
{
	u32 lnh = 0;
	u8 opcode = 0;
	struct hfi1_ib_header *hdr;
	struct hfi1_other_headers *ohdr = NULL;
	int ret;

	ret = hfi1_filter_check(ibhdr, "header");
	if (ret)
		return ret;
	ret = hfi1_filter_check(value, "user");
	if (ret)
		return ret;

	hdr = (struct hfi1_ib_header *)ibhdr;

	lnh = (be16_to_cpu(hdr->lrh[0]) & 3);

	if (lnh == HFI1_LRH_BTH)
		ohdr = &hdr->u.oth;
	else if (lnh == HFI1_LRH_GRH)
		ohdr = &hdr->u.l.oth;
	else
		return HFI1_FILTER_ERR;

	opcode = be32_to_cpu(ohdr->bth[0]) >> 24;

	if (*((u8 *)value) == ((opcode >> 5) & 0x7))
		return HFI1_FILTER_HIT;

	return HFI1_FILTER_MISS;
}
