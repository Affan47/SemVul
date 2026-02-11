input_block_level_for_recursive(Block *first_block)
{

    Block *bpt;
    Module_table *mpt;

    for (bpt = first_block; bpt != NULL; bpt = bpt->next) {
	if (bpt->inner != NULL) {
	    input_block_level_for_recursive(bpt->inner);
	}

	if (bpt->kind == SB) {
	    mpt = search_module_for_sb(bpt);
	    if( mpt->block_head->hierarchical_level > 0 && !is_sb_func(bpt) ){
		bpt->hierarchical_level = mpt->block_head->hierarchical_level;
		bpt->inline_level = mpt->block_head->inline_level;
		bpt->inline_div_loop_level = mpt->block_head->inline_div_loop_level;

	    }else{
		bpt->hierarchical_level = mpt->block_head->cost;
		bpt->inline_level =  mpt->block_head->cost;
		bpt->inline_div_loop_level = mpt->block_head->cost;
	    }
	}
    }
}
