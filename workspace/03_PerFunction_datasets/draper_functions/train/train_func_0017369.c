_load_port(int fd, ibnd_fabric_cache_t * fabric_cache)
{
	uint8_t buf[IBND_FABRIC_CACHE_BUFLEN];
	ibnd_port_cache_t *port_cache = NULL;
	ibnd_port_t *port = NULL;
	size_t offset = 0;
	uint8_t tmp8;

	port_cache = (ibnd_port_cache_t *) malloc(sizeof(ibnd_port_cache_t));
	if (!port_cache) {
		IBND_DEBUG("OOM: port_cache\n");
		return -1;
	}
	memset(port_cache, '\0', sizeof(ibnd_port_cache_t));

	port = (ibnd_port_t *) malloc(sizeof(ibnd_port_t));
	if (!port) {
		IBND_DEBUG("OOM: port\n");
		free(port_cache);
		return -1;
	}
	memset(port, '\0', sizeof(ibnd_port_t));

	port_cache->port = port;

	if (ibnd_read(fd, buf, IBND_PORT_CACHE_LEN) < 0)
		goto cleanup;

	offset += _unmarshall64(buf + offset, &port->guid);
	offset += _unmarshall8(buf + offset, &tmp8);
	port->portnum = tmp8;
	offset += _unmarshall8(buf + offset, &tmp8);
	port->ext_portnum = tmp8;
	offset += _unmarshall16(buf + offset, &port->base_lid);
	offset += _unmarshall8(buf + offset, &port->lmc);
	offset += _unmarshall_buf(buf + offset, port->info, IB_SMP_DATA_SIZE);
	offset += _unmarshall64(buf + offset, &port_cache->node_guid);
	offset += _unmarshall8(buf + offset, &port_cache->remoteport_flag);
	offset +=
	    _unmarshall64(buf + offset, &port_cache->remoteport_cache_key.guid);
	offset +=
	    _unmarshall8(buf + offset,
			 &port_cache->remoteport_cache_key.portnum);

	store_port_cache(port_cache, fabric_cache);

	return 0;

cleanup:
	free(port);
	free(port_cache);
	return -1;
}
