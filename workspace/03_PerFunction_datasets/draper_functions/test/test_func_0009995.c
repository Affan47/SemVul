brcmf_proto_bcdc_hdrpush(struct brcmf_pub *drvr, int ifidx, u8 offset,
			 struct sk_buff *pktbuf)
{
	struct brcmf_proto_bcdc_header *h;

	brcmf_dbg(BCDC, "Enter\n");


	skb_push(pktbuf, BCDC_HEADER_LEN);

	h = (struct brcmf_proto_bcdc_header *)(pktbuf->data);

	h->flags = (BCDC_PROTO_VER << BCDC_FLAG_VER_SHIFT);
	if (pktbuf->ip_summed == CHECKSUM_PARTIAL)
		h->flags |= BCDC_FLAG_SUM_NEEDED;

	h->priority = (pktbuf->priority & BCDC_PRIORITY_MASK);
	h->flags2 = 0;
	h->data_offset = offset;
	BCDC_SET_IF_IDX(h, ifidx);
	trace_brcmf_bcdchdr(pktbuf->data);
}
