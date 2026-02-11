op_ret( uint32_t op, const struct opinfo *oi)
{
	REGS16_W(gbcpu_regs, PC, pop());
	DPRINTF(" %s", oi->name);
}
