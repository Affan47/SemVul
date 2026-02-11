rdp_write_multifragment_update_capability_set(STREAM* s, rdpSettings* settings)
{
	uint8* header;

	header = rdp_capability_set_start(s);

	stream_write_uint32(s, settings->multifrag_max_request_size);

	rdp_capability_set_finish(s, header, CAPSET_TYPE_MULTI_FRAGMENT_UPDATE);
}
