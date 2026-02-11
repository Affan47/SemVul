iterate_dom_frontier_set(struct compilation_unit *cu,
				struct var_info *var,
				struct basic_block *bb,
				struct bitset *workset,
				unsigned long *inserted,
				unsigned long *work,
				int *last_ndx)
{
	struct bitset *temp_dom_frontier;
	struct basic_block *bb_ndx;
	int ndx;

	temp_dom_frontier = alloc_bitset(nr_bblocks(cu));

	bitset_copy_to(bb->dom_frontier, temp_dom_frontier);

	ndx = 0;
	while ((ndx = bitset_ffs_from(temp_dom_frontier, ndx)) != -1) {
		clear_bit(temp_dom_frontier->bits, ndx);

		bb_ndx = cu->bb_df_array[ndx];
		if (inserted[ndx] != var->vreg && test_bit(bb_ndx->live_in_set->bits, var->vreg)) {
			inserted[ndx] = var->vreg;
			insert_phi(bb_ndx, var);

			if (work[ndx] != var->vreg) {
				set_bit(workset->bits, ndx);
				work[ndx] = var->vreg;
				if (ndx < *last_ndx)
					*last_ndx = ndx;
			}
		}
	}

	free(temp_dom_frontier);

}
