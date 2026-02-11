op_call( uint32_t op, const struct opinfo *oi)
{
	uint16_t ofs = get_imm16();

	DPRINTF(" %s 0x%04x", oi->name, ofs);
	push(REGS16_R(gbcpu_regs, PC));
	REGS16_W(gbcpu_regs, PC, ofs);
}
