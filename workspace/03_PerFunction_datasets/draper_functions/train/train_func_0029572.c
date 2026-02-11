kgdb_arch_set_breakpoint(struct kgdb_bkpt *bpt)
{
	int err;

	err = probe_kernel_read(bpt->saved_instr, (char *)bpt->bpt_addr,
				BREAK_INSTR_SIZE);
	if (err)
		return err;
	err = probe_kernel_write((char *)bpt->bpt_addr,
				 arch_kgdb_ops.gdb_bpt_instr, BREAK_INSTR_SIZE);
	return err;
}
