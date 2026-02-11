lad_sm_search_array_min(StripMining *sm,
			StripMiningInnerLoop *smil,
			Block *search_block,
			LoopDat *lpdat,
			int step, int entry, int dim)
{

    int min, min_pre, min_post, min_pe, min_inner;


    if (search_block == NULL) {
	return INT_MAX;
    }

    min_inner = INT_MAX;
    min_pre = lad_sm_search_array_min_pe_statement(sm,
						   smil,
						   search_block->pre_head,
						   lpdat,
						   step,
						   entry,
						   dim);

    min_post = lad_sm_search_array_min_pe_statement(sm,
						    smil,
						    search_block->post_head,
						    lpdat,
						    step,
						    entry,
						    dim);
    min_pe = (min_pre <= min_post ? min_pre : min_post);

    if (search_block->inner != NULL) {
	min_inner = lad_sm_search_array_min_inner_block(sm,
							smil,
							search_block->inner,
							lpdat,
							step,
							entry,
							dim);

    }
    min = (min_pe <= min_inner ? min_pe : min_inner);

    return min;
}
