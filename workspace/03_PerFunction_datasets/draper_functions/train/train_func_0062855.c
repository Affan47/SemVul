print_node_desc(ib_node_record_t * node_record)
{
	ib_node_info_t *p_ni = &(node_record->node_info);
	ib_node_desc_t *p_nd = &(node_record->node_desc);
	char *name;

	if (p_ni->node_type == IB_NODE_TYPE_CA) {
		name = remap_node_name(node_name_map,
					node_record->node_info.node_guid,
					(char *)p_nd->description);
		printf("%6d  \"%s\"\n", cl_ntoh16(node_record->lid), name);
		free(name);
	}
}
