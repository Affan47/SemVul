free_up_hreg (MonoCompile *cfg, MonoBasicBlock *bb, MonoInst **last, MonoInst *ins, int hreg, int bank)
{
	if (G_UNLIKELY (bank)) {
		if (!(cfg->rs->free_mask [bank] & (regmask (hreg)))) {
			bank = translate_bank (cfg->rs, bank, hreg);
			DEBUG (printf ("\tforced spill of R%d\n", cfg->rs->symbolic [bank] [hreg]));
			spill_vreg (cfg, bb, last, ins, cfg->rs->symbolic [bank] [hreg], bank);
		}
	}
	else {
		if (!(cfg->rs->ifree_mask & (regmask (hreg)))) {
			DEBUG (printf ("\tforced spill of R%d\n", cfg->rs->isymbolic [hreg]));
			spill_vreg (cfg, bb, last, ins, cfg->rs->isymbolic [hreg], bank);
		}
	}
}
