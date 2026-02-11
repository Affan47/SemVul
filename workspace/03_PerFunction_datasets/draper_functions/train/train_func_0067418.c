dht_selfheal_layout_maximize_overlap (call_frame_t *frame, loc_t *loc,
				      dht_layout_t *new, dht_layout_t *old)
{
	int           i            = 0;
	int           j            = 0;
	uint32_t      curr_overlap = 0;
	uint32_t      max_overlap  = 0;
	int           max_overlap_idx = -1;
	uint32_t      overlap      = 0;
        uint32_t     *table = NULL;

	dht_layout_sort_volname (old);


        table = alloca(sizeof(overlap)*old->cnt*new->cnt);
        if (!table) {
                return;
        }
        memset(table,0,sizeof(overlap)*new->cnt*new->cnt);
        for (i = 0; i < new->cnt; ++i) {
                for (j = 0; j < old->cnt; ++j) {
                        OV_ENTRY(i,j) = dht_overlap_calc(old,j,new,i);
                }
        }

	for (i = 0; i < new->cnt; i++) {
		if (new->list[i].err > 0) {


			continue;
                }

                max_overlap = 0;
                max_overlap_idx = i;
                for (j = (i + 1); j < new->cnt; ++j) {
                        if (new->list[j].err > 0) {


			        continue;
                        }

                        curr_overlap = OV_ENTRY(i,i) + OV_ENTRY(j,j);

                        overlap = OV_ENTRY(i,j) + OV_ENTRY(j,i);

                        if (overlap > curr_overlap) {
                                overlap -= curr_overlap;

                                if (overlap > max_overlap) {
                                        max_overlap = overlap;
                                        max_overlap_idx = j;
                                }
                        }
                }

		if (max_overlap_idx != i) {
 			dht_layout_range_swap (new, i, max_overlap_idx);

                        for (j = 0; j < old->cnt; ++j) {
                                overlap = OV_ENTRY(i,j);
                                OV_ENTRY(i,j) = OV_ENTRY(max_overlap_idx,j);
                                OV_ENTRY(max_overlap_idx,j) = overlap;
                        }
                }
	}
}
