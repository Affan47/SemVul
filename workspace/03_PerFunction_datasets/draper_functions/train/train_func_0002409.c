free_ssa_liveness(struct compilation_unit *cu)
{
	struct basic_block *bb;

	for_each_basic_block(bb, &cu->bb_list) {
		free(bb->def_set);
		free(bb->use_set);
		free(bb->live_in_set);
		free(bb->live_out_set);
	}
}
