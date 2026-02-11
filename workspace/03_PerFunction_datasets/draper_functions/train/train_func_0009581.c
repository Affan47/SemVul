activecpu_get_pc_byte(void)
{
	offs_t base, pc;
	int shift;

	VERIFY_ACTIVECPU(0, activecpu_get_pc_byte);
	shift = cpu[activecpu].intf.address_shift;
	base = cpu[activecpu].intf.pgm_memory_base;
	pc = (*cpu[activecpu].intf.get_reg)(REG_PC);
	return base + ((shift < 0) ? (pc << -shift) : (pc >> shift));
}
