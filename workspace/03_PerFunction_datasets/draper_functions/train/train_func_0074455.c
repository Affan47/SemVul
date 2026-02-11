ars_compiler_ipopt(struct ars_packet *pkt, int layer)
{
	int j, opt_size;


	if (layer != ARS_MAX_LAYER-1 &&
	    pkt->p_layer[layer+1].l_type == ARS_TYPE_IPOPT)
		return ARS_OK;


	j = layer - 1;
	while (j < ARS_MAX_LAYER && j >= 0 &&
	       pkt->p_layer[j].l_type == ARS_TYPE_IPOPT)
		j--;
	j++;
	__D(printf("First IP OPTION layer is %d\n", j);)
	opt_size = ars_relative_size(pkt, j) - ars_relative_size(pkt, layer+1);
	__D(printf("IP OPTION size %d\n", opt_size);)
	if (opt_size % 4) {
		int padding = 4 - (opt_size % 4);
		unsigned char *t;
		int cur_size = pkt->p_layer[layer].l_size;

		__D(printf("IP OPTION at layer %d needs %d bytes "
			   "of padding\n", layer, padding);)
		t = realloc(pkt->p_layer[layer].l_data, cur_size + padding);
		if (t == NULL) {
			ars_set_error(pkt, "Out of memory padding IP options");
			return -ARS_NOMEM;
		}
		memset(t+cur_size, ARS_IPOPT_NOP, padding);
		__D(printf("The last IP OPTION length was: %d\n", cur_size);)
		pkt->p_layer[layer].l_data = t;
		pkt->p_layer[layer].l_size += padding;
		__D(printf("After padding it is: %d\n", pkt->p_layer[layer].l_size);)
	}
	return -ARS_OK;
}
