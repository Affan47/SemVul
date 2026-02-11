send_packet(private_task_manager_t *this, bool request,
						packet_t *packet)
{
	bool use_frags = FALSE;
	ike_cfg_t *ike_cfg;
	chunk_t data;

	ike_cfg = this->ike_sa->get_ike_cfg(this->ike_sa);
	if (ike_cfg)
	{
		switch (ike_cfg->fragmentation(ike_cfg))
		{
			case FRAGMENTATION_FORCE:
				use_frags = TRUE;
				break;
			case FRAGMENTATION_YES:
				use_frags = this->ike_sa->supports_extension(this->ike_sa,
														EXT_IKE_FRAGMENTATION);
				break;
			default:
				break;
		}
	}
	data = packet->get_data(packet);
	if (data.len > this->frag.size && use_frags)
	{
		fragment_payload_t *fragment;
		u_int8_t num, count;
		size_t len, frag_size;
		host_t *src, *dst;

		src = packet->get_source(packet);
		dst = packet->get_destination(packet);

		frag_size = this->frag.size;
		if (dst->get_port(dst) != IKEV2_UDP_PORT &&
			src->get_port(src) != IKEV2_UDP_PORT)
		{
			frag_size -= 4;
		}
		count = data.len / frag_size + (data.len % frag_size ? 1 : 0);

		DBG1(DBG_IKE, "sending IKE message with length of %zu bytes in "
			 "%hhu fragments", data.len, count);
		for (num = 1; num <= count; num++)
		{
			len = min(data.len, frag_size);
			fragment = fragment_payload_create_from_data(num, num == count,
												chunk_create(data.ptr, len));
			if (!send_fragment(this, request, src, dst, fragment))
			{
				packet->destroy(packet);
				return FALSE;
			}
			data = chunk_skip(data, len);
		}
		packet->destroy(packet);
		return TRUE;
	}
	charon->sender->send(charon->sender, packet);
	return TRUE;
}
