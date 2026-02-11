store_operand(struct sim_device *dev,
			  int amode, int reg, int is_byte,
			  uint16_t addr, uint16_t data)
{
	if (is_byte)
		MEM_SETB(dev, addr, data);
	else
		MEM_SETW(dev, addr, data);

	if (amode == MSP430_AMODE_REGISTER)
		dev->regs[reg] = data;
	else if (addr < MEM_IO_END && dev->store_func)
		dev->store_func(dev->user_data, dev->current_insn,
				addr, is_byte, data);
}
