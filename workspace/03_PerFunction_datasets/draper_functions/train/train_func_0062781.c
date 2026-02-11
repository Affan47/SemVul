ssa_to_lir(struct compilation_unit *cu)
{
	int err;

	insert_instruction_pass(cu);

	err = ssa_deconstruction(cu);
	if (err)
		return err;

	recompute_insn_positions(cu);

	replace_var_infos(cu);
	free_ssa(cu);

	create_fixed_var_infos(cu);
	cumulate_fixed_var_infos(cu);

	return 0;
}
