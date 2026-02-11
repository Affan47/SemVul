alloc_reg (MonoCompile *cfg, MonoBasicBlock *bb, MonoInst **last, MonoInst *ins, regmask_t dest_mask, int sym_reg, RegTrack *info, int bank)
{
	if (G_UNLIKELY (bank))
		return alloc_general_reg (cfg, bb, last, ins, dest_mask, sym_reg, bank);
	else
		return alloc_int_reg (cfg, bb, last, ins, dest_mask, sym_reg, info);
}
