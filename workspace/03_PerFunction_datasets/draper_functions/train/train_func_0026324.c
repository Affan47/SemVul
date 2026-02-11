write_pixel_shiftreg(offs_t offset,data32_t data)
{
	if (state.config->from_shiftreg)
		state.config->from_shiftreg(offset, &state.shiftreg[0]);
#if 0
	else
		logerror("From ShiftReg function not set. PC = %08X\n", PC);
#endif
}
