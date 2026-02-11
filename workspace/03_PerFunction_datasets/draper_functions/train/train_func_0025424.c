select_nodeinfo_pack(select_nodeinfo_t *nodeinfo, Buf buffer,
				uint16_t protocol_version)
{
	ListIterator itr;
	node_subgrp_t *subgrp = NULL;
	uint16_t count = 0;

	if (protocol_version >= SLURM_2_5_PROTOCOL_VERSION) {
		pack16(nodeinfo->bitmap_size, buffer);

		packstr(nodeinfo->extra_info, buffer);
		packstr(nodeinfo->failed_cnodes, buffer);

		if (nodeinfo->ba_mp)
			packstr(nodeinfo->ba_mp->loc, buffer);
		else
			packstr(nodeinfo->rack_mp, buffer);

		if (nodeinfo->subgrp_list)
			count = list_count(nodeinfo->subgrp_list);

		pack16(count, buffer);

		if (count > 0) {
			itr = list_iterator_create(nodeinfo->subgrp_list);
			while ((subgrp = list_next(itr))) {
				_pack_node_subgrp(subgrp, buffer,
						  protocol_version);
			}
			list_iterator_destroy(itr);
		}
	} else {
 		error("select_nodeinfo_pack: protocol_version "
 		      "%hu not supported", protocol_version);
	}

	return SLURM_SUCCESS;
}
