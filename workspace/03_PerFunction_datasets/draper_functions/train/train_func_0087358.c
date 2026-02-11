kdb_handle_bp(struct pt_regs *regs, kdb_bp_t *bp)
{
	if (KDB_DEBUG(BP))
		kdb_printf("regs->ip = 0x%lx\n", instruction_pointer(regs));


	kdb_setsinglestep(regs);


	bp->bp_delay = 0;
	bp->bp_delayed = 1;
}
