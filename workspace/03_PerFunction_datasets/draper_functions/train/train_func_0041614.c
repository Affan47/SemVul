gdbstub_continue ( struct gdbstub *stub, int single_step ) {
	gdbreg_t pc;
	if ( stub->len > 1 && gdbstub_get_packet_args ( stub, &pc, 1, NULL ) ) {
		gdbmach_set_pc ( stub->regs, pc );
	}
	gdbmach_set_single_step ( stub->regs, single_step );
	stub->exit_handler = 1;

}
