op_bit(uint32_t op)
{
	long reg = op & 7;
	unsigned long bit = (op >> 3) & 7;

	DPRINTF("\tBIT %ld, ", bit);
	print_reg(reg);
	gbcpu_regs.rn.f &= ~NF;
	gbcpu_regs.rn.f |= HF | ZF;
	gbcpu_regs.rn.f ^= ((get_reg(reg) << 8) >> (bit+1)) & ZF;
}
