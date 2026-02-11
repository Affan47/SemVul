_node_state_dealloc(gres_state_t *gres_ptr)
{
	int i;
	gres_node_state_t *gres_node_ptr;
	char *gres_name = NULL;

	gres_node_ptr = (gres_node_state_t *) gres_ptr->gres_data;
	gres_node_ptr->gres_cnt_alloc = 0;
	if (gres_node_ptr->gres_bit_alloc) {
		int i = bit_size(gres_node_ptr->gres_bit_alloc) - 1;
		if (i >= 0)
			bit_nclear(gres_node_ptr->gres_bit_alloc, 0, i);
	}
	if (gres_node_ptr->topo_cnt && !gres_node_ptr->topo_gres_cnt_alloc) {
		for (i=0; i<gres_context_cnt; i++) {
			if (gres_ptr->plugin_id == gres_context[i].plugin_id) {
				gres_name = gres_context[i].gres_name;
				break;
			}
		}
		error("gres_plugin_node_state_dealloc_all: gres/%s topo_cnt!=0 "
		      "and topo_gres_cnt_alloc is NULL", gres_name);
	} else if (gres_node_ptr->topo_cnt) {
		for (i=0; i<gres_node_ptr->topo_cnt; i++) {
			gres_node_ptr->topo_gres_cnt_alloc[i] = 0;
		}
	} else {


		xfree(gres_node_ptr->topo_gres_cnt_alloc);
	}
}
