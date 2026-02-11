step_cpu(struct sim_device *dev)
{
	uint16_t ins;
	int ret;


	dev->current_insn = dev->regs[MSP430_REG_PC];
	ins = MEM_GETW(dev, dev->current_insn);
	dev->regs[MSP430_REG_PC] += 2;


	if ((ins & 0xf000) >= 0x4000)
		ret = step_double(dev, ins);
	else if ((ins & 0xf000) >= 0x2000)
		ret = step_jump(dev, ins);
	else
		ret = step_single(dev, ins);


	if (ret < 0)
		dev->regs[MSP430_REG_PC] = dev->current_insn;

	return ret;
}
