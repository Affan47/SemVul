lad_sm_search_array_width_inner_block(StripMining *sm,
				      Block *search_block,
				      int step,
				      int entry,
				      int dim,
				      int *width)
{
    Block *bpt;

    for (bpt = search_block; bpt != NULL; bpt = bpt->next) {
	lad_sm_search_array_width_pe_statement(sm,
					       bpt->pre_head,
					       step,
					       entry,
					       dim,
					       width);
	lad_sm_search_array_width_pe_statement(sm,
					       bpt->post_head,
					       step,
					       entry,
					       dim,
					       width);
    }

    if (bpt->inner != NULL) {
	lad_sm_search_array_width_inner_block(sm,
					      bpt->inner,
					      step,
					      entry,
					      dim,
					      width);
    }
}
