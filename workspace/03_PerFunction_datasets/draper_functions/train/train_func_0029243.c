needs_ram(int cpunum, void *handler)
{

	if (HANDLER_IS_RAM(handler) || HANDLER_IS_ROM(handler) || HANDLER_IS_RAMROM(handler) || HANDLER_IS_BANK(handler))
		return 1;


	else if (HANDLER_IS_NOP(handler))
		return 0;


	else
		return IS_SPARSE(cpudata[cpunum].mem.abits);
}
