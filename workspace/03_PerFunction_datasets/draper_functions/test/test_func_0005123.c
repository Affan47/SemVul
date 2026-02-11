command_status(int argc, char **argv)
{
	uint8_t	status;

	status = ccdbg_read_status(s51_dbg);
	if ((status & CC_STATUS_CHIP_ERASE_DONE) == 0)
		s51_printf("\tChip erase in progress\n");
	if (status & CC_STATUS_PCON_IDLE)
		s51_printf("\tCPU is idle (clock gated)\n");
	if (status & CC_STATUS_CPU_HALTED)
		s51_printf("\tCPU halted\n");
	else
		s51_printf("\tCPU running\n");
	if ((status & CC_STATUS_POWER_MODE_0) == 0)
		s51_printf("\tPower Mode 1-3 selected\n");
	if (status & CC_STATUS_HALT_STATUS)
		s51_printf("\tHalted by software or hw breakpoint\n");
	else
		s51_printf("\tHalted by debug command\n");
	if (status & CC_STATUS_DEBUG_LOCKED)
		s51_printf("\tDebug interface is locked\n");
	if ((status & CC_STATUS_OSCILLATOR_STABLE) == 0)
		s51_printf("\tOscillators are not stable\n");
	if (status & CC_STATUS_STACK_OVERFLOW)
		s51_printf("\tStack overflow\n");
	return command_success;
}
