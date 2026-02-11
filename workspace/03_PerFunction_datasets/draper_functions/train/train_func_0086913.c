cc_stopped(uint8_t status)
{
	uint16_t pc;
	int b;
	int code;
	char *reason;

	pc = ccdbg_get_pc(s51_dbg);
	if (status & CC_STATUS_CPU_HALTED) {
		if ((status & CC_STATUS_HALT_STATUS) != 0) {
			pc = pc - 1;
			code = 104;
			reason = "Breakpoint";
			b = find_breakpoint(pc);
			if (b != -1 && breakpoints[b].temporary)
				clear_breakpoint(pc, 1);
			ccdbg_set_pc(s51_dbg, pc);
		} else {
			code = 105;
			reason = "Interrupt";
		}
		s51_printf("Stop at 0x%04x: (%d) %s\n",
			pc, code, reason);
	}
}
