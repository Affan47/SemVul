backpatch_lookupswitch(struct lookupswitch *table)
{
	for (unsigned int i = 0; i < table->count; i++) {
		int idx = bb_lookup_successor_index(table->src,
						    table->pairs[i].bb_target);

		if (branch_needs_resolution_block(table->src, idx)) {
			table->pairs[i].target =
				(void *)table->src->resolution_blocks[idx].addr;
		} else {
			table->pairs[i].target =
				bb_native_ptr(table->pairs[i].bb_target);
		}
	}
}
