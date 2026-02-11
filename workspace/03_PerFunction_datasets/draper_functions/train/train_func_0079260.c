alloc_general_reg (MonoCompile *cfg, MonoBasicBlock *bb, MonoInst **last, MonoInst *ins, regmask_t dest_mask, int sym_reg, int bank)
{
	int val;

	val = mono_regstate_alloc_general (cfg->rs, dest_mask, bank);

	if (val < 0)
		val = get_register_spilling (cfg, bb, last, ins, dest_mask, sym_reg, bank);

	return val;
}
