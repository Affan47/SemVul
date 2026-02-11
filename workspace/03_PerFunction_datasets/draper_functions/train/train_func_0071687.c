lad_sm_iteration_load_middle_make_dtu_trans_group(StripMining *sm,
						  Block *smil_block,
						  Array_def_use_table_semnode *load,
						  Array_table *ldm,
						  int dim,
						  SemTree *prev_lower,
						  SemTree *prev_upper,
						  SemTree *next_lower,
						  SemTree *next_upper)
{
    Dtu_trans_group *dtg;
    Array_table *stbl, *dtbl, *source, *destination, *lm;
    Array_def_use_table_semnode *load_dtg;
    Array_range_semnode *destination_range, *source_range;

    semtree_process(prev_lower);
    semtree_process(prev_upper);
    semtree_process(next_lower);
    semtree_process(next_upper);

    load_dtg = copy_array_def_use_table_semnode(load);
    lm = lad_sm_change_csm_to_lm(smil_block->module, load_dtg->entry);

    dtg = get_dtu_trans_group();
    source = lad_sm_change_csm_to_lm(smil_block->module, load_dtg->entry);
    destination = lad_sm_change_csm_to_lm(smil_block->module,
					  load_dtg->entry);
    stbl = search_array_table(smil_block->module->array_head, source->entry);
    dtbl = search_array_table(smil_block->module->array_head,
			      destination->entry);

    source_range = copy_array_range_semnode(load_dtg->region_head->dim_head);
    destination_range =
	copy_array_range_semnode(load_dtg->region_head->dim_head);

    lad_sm_dtu_load_source_ary_dim(source_range,
				   dim,
				   prev_lower,
				   prev_upper);

    lad_sm_dtu_load_source_ary_dim(destination_range,
				   dim,
				   next_lower,
				   next_upper);

    if (opt_lad_sm_cmp_debug) {
	printf("load middle entry : %d\n", lm->entry);
	print_array_range_semnode(source_range);
	print_array_range_semnode(destination_range);
    }
    dtg->entry_head = make_dtu_entry_table(source_range,
					   destination_range,
					   0,
					   0,
					   0,
					   0,
					   DTU_CONT,
					   DTU_LOAD,
					   stbl,
					   dtbl);

    fit_link_and_set_dtu_group(dtg, dtg->entry_head);

    return dtg;
}
