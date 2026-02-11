do_receive_frame(faifa_t *faifa, void *buf, int len, void *UNUSED(user))
{
	struct ether_header *eth_header = buf;
	u_int16_t *eth_type = &(eth_header->ether_type);
	u_int8_t *frame_ptr = (u_int8_t *)buf, *payload_ptr;
	int frame_len = len, payload_len;

	payload_ptr = frame_ptr + sizeof(*eth_header);
	payload_len = frame_len - sizeof(*eth_header);
	if (*eth_type == ETHERTYPE_8021Q) {
		payload_ptr += 4;
		payload_len -= 4;
		eth_type = (u_int16_t *)(payload_ptr - 2);
	}


	if (!(*eth_type == ntohs(ETHERTYPE_HOMEPLUG)) && !(*eth_type == ntohs(ETHERTYPE_HOMEPLUG_AV)))
		return;

	faifa_printf(out_stream, "\nDump:\n");

	if (*eth_type == ntohs(ETHERTYPE_HOMEPLUG))
		hp10_dump_frame(payload_ptr, payload_len);
	else if (*eth_type == ntohs(ETHERTYPE_HOMEPLUG_AV))
		hpav_dump_frame(payload_ptr, payload_len, eth_header);


	if (faifa->verbose)
		dump_hex_blob(faifa, frame_ptr, frame_len);
}
