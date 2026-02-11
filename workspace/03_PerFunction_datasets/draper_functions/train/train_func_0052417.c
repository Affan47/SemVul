hfi1_filter_ib_service_level(void *ibhdr, void *packet_data,
					void *value)
{
	struct hfi1_ib_header *hdr;
	int ret;

	ret = hfi1_filter_check(ibhdr, "header");
	if (ret)
		return ret;
	ret = hfi1_filter_check(value, "user");
	if (ret)
		return ret;

	hdr = (struct hfi1_ib_header *)ibhdr;

	if ((*((u8 *)value)) == ((be16_to_cpu(hdr->lrh[0]) >> 4) & 0xF))
		return HFI1_FILTER_HIT;

	return HFI1_FILTER_MISS;
}
