isns_build_objs(isns_portal_info_t *portal_info,
			   isns_object_list_t *objs)
{
	struct isns_node_list *node;
	isns_object_t *inode, *entity;
	unsigned int i, nportals = 1;
	int rc = 0;

	log_debug(7, "isns_build_objs");


	if (isns_portal_is_wildcard(portal_info)) {
		static isns_portal_info_t *iflist;

		nportals = isns_get_nr_portals();
		log_debug(4, "got %d portals", nportals);
		if (!nportals)
			return ISCSI_ERR_NO_OBJS_FOUND;

		iflist = calloc(nportals, sizeof(isns_portal_info_t));
		if (!iflist) {
			log_error("Unable to allocate %d portals.", nportals);
			return ISCSI_ERR_NOMEM;
		}

		nportals = isns_enumerate_portals(iflist, nportals);
		if (nportals == 0) {
			log_error("Unable to enumerate portals - "
				  "no usable interfaces found");
			free(iflist);
			return ISCSI_ERR_NO_OBJS_FOUND;
		}
		for (i = 0; i < nportals; ++i) {
			iflist[i].addr.sin6_port = portal_info->addr.sin6_port;
			iflist[i].proto = portal_info->proto;
		}
		portal_info = iflist;
	}

	if (!isns_entity_id) {
		isns_entity_id = calloc(1, 256);
		if (!isns_entity_id)
			return ISCSI_ERR_NOMEM;

		rc = getnameinfo((struct sockaddr *) &portal_info->addr,
				 sizeof(portal_info->addr),
				 isns_entity_id, 256, NULL, 0, 0);
		if (rc) {
			free(isns_entity_id);
			isns_entity_id = NULL;

			log_error("Could not get hostname for EID.");
			return ISCSI_ERR;
		}
	}

	entity = isns_create_entity(ISNS_ENTITY_PROTOCOL_ISCSI, isns_entity_id);
	if (!entity) {
		log_error("Could not create iSNS entity.");
		return ISCSI_ERR_NOMEM;
	}
	isns_object_list_append(objs, entity);

	for (i = 0; i < nportals; ++i, ++portal_info) {
		isns_object_t *portal;

		portal = isns_create_portal(portal_info, entity);
		if (!portal) {
			rc = ISCSI_ERR_NOMEM;
			goto fail;
		}
		isns_object_list_append(objs, portal);

		if (!isns_object_set_uint32(portal, ISNS_TAG_SCN_PORT,
				isns_portal_tcpudp_port(portal_info))) {
			rc = ISCSI_ERR_INVAL;
			goto fail;
		}
	}

	list_for_each_entry(node, &isns_initiators, list) {
		inode = isns_create_storage_node2(node->source,
						  ISNS_ISCSI_INITIATOR_MASK,
						  NULL);
		if (!inode) {
			rc = ISCSI_ERR_NOMEM;
			goto fail;
		}
		isns_object_list_append(objs, inode);
	}

	return 0;
fail:
	isns_object_list_destroy(objs);
	return rc;
}
