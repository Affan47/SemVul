rgb_to_alpha_remap (
	struct rc_instruction * inst,
	struct rc_pair_instruction_arg * arg,
	rc_register_file old_file,
	rc_swizzle old_swz,
	unsigned int new_index)
{
	int new_src_index;
	unsigned int i;

	for (i = 0; i < 3; i++) {
		if (get_swz(arg->Swizzle, i) == old_swz) {
			SET_SWZ(arg->Swizzle, i, RC_SWIZZLE_W);
		}
	}
	new_src_index = rc_pair_alloc_source(&inst->U.P, 0, 1,
							old_file, new_index);


	if (new_src_index < 0) {
		assert(0);
		return;
	}

	arg->Source = new_src_index;
}
