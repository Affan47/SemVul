op_cp_imm( uint32_t op, const struct opinfo *oi)
{
	uint8_t imm = get_imm8();
	uint8_t old = gbcpu_regs.rn.a;
	uint8_t new = old;

	DPRINTF(" %s A, $0x%02x", oi->name, imm);
	new -= imm;
	gbcpu_regs.rn.f = NF;
	if (old < new) gbcpu_regs.rn.f |= CF;
	if ((old & 15) < (new & 15)) gbcpu_regs.rn.f |= HF;
	if (new == 0) gbcpu_regs.rn.f |= ZF;
}
