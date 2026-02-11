cyclic_update_info_gf3(PACKED_MATRIX_GF3 *G, INFO *info) {
	short i, d, w;


	info->lower_bound = (info->info_weight_completed + 1) * G->nFullRankMatrices;
	info->lower_bound = (unsigned int)
		ceil(((double)G->block_length/(double)G->dimension)*((double)info->info_weight_completed+1.0));


	switch (info->weight_constraint) {
		case C_0MOD3: info->displayed_lower_bound = ROUND_0_MOD_3(info->lower_bound); break;
		default: info->displayed_lower_bound = info->lower_bound;
	}


	d = 0;
	for (i=info->info_weight_completed+1;;i++) {
		w = (unsigned int)
			ceil(((double)G->block_length/(double)G->dimension)*((double)i+1.0));
		switch (info->weight_constraint) {
			case C_0MOD3: d = ROUND_0_MOD_3(w); break;
			default: d = w;
		}
		if (d >= info->upper_bound) { info->max_info_weight_req = i; break; }
	}
}
