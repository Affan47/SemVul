get_ts_from_subnet(private_id_payload_t *this,
											  ts_type_t type)
{
	traffic_selector_t *ts;
	chunk_t net, netmask;
	int i;

	net = chunk_create(this->id_data.ptr, this->id_data.len / 2);
	netmask = chunk_clone(chunk_skip(this->id_data, this->id_data.len / 2));
	for (i = 0; i < net.len; i++)
	{
		netmask.ptr[i] = (netmask.ptr[i] ^ 0xFF) | net.ptr[i];
	}
	ts = traffic_selector_create_from_bytes(this->protocol_id, type,
								net, this->port, netmask, this->port ?: 65535);
	chunk_free(&netmask);
	return ts;
}
