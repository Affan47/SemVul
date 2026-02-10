mmu_op(uae_u32 opcode, uae_u16 )
{
	if ((opcode & 0xFE0) == 0x0500) {

		flush_internals();
	} else if ((opcode & 0x0FD8) == 0x548) {

	} else
		op_illg(opcode);
}
