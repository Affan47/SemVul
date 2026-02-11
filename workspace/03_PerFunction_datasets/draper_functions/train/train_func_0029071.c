isns_process_esi(isns_server_t *srv, isns_simple_t *call, isns_simple_t **reply)
{
	const isns_attr_list_t *attrs = &call->is_message_attrs;
	isns_object_t	*portal = NULL;


	*reply = isns_simple_create(ISNS_ENTITY_STATUS_INQUIRY,
				srv->is_source, attrs);


	if (srv->is_db && attrs->ial_count == 4) {
		const isns_attr_t	*addr_attr, *port_attr;

		addr_attr = attrs->ial_data[2];
		port_attr = attrs->ial_data[3];
		if (addr_attr->ia_tag_id == ISNS_TAG_PORTAL_IP_ADDRESS
		 && port_attr->ia_tag_id == ISNS_TAG_PORTAL_TCP_UDP_PORT) {
			isns_attr_list_t key;

			key.ial_count = 2;
			key.ial_data = attrs->ial_data + 2;
			portal = isns_db_lookup(srv->is_db,
					&isns_portal_template,
					&key);
		}

		if (portal)
			portal->ie_mtime = time(NULL);
	}
	return ISNS_SUCCESS;
}
