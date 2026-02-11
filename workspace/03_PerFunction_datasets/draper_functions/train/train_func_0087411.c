lad_sm_search_array_max_inner_block(StripMining *sm,
				    StripMiningInnerLoop *smil,
				    Block *search_block,
				    LoopDat *lpdat,
				    int step,
				    int entry,
				    int dim)
{
    Block *bpt;
    int max, max_all, max_inner, max_pre, max_post, max_pe;

    max = INT_MIN;
    max_all = INT_MIN;
    max_inner = INT_MIN;

    for (bpt = search_block; bpt != NULL; bpt = bpt->next) {
	max_pre = lad_sm_search_array_max_pe_statement(sm,
						       smil,
						       bpt->pre_head,
						       lpdat,
						       step,
						       entry,
						       dim);

	max_post = lad_sm_search_array_max_pe_statement(sm,
							smil,
							bpt->post_head,
							lpdat,
							step,
							entry,
							dim);
	max_pe = (max_pre >= max_post ? max_pre : max_post);

	if (bpt->inner != NULL) {
	    max_inner = lad_sm_search_array_max_inner_block(sm,
							    smil,
							    bpt->inner,
							    lpdat,
							    step,
							    entry,
							    dim);
	}
	max = (max_pe >= max_inner ? max_pe : max_inner);

    }
    max_all = (max >= max_all ? max : max_all);
    return max_all;
}
