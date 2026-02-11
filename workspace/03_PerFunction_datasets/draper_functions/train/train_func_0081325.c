accept_addr_byte(struct nandsim *ns, u_char bt)
{
	uint byte = (uint)bt;

	if (ns->regs.count < (ns->geom.pgaddrbytes - ns->geom.secaddrbytes))
		ns->regs.column |= (byte << 8 * ns->regs.count);
	else {
		ns->regs.row |= (byte << 8 * (ns->regs.count -
						ns->geom.pgaddrbytes +
						ns->geom.secaddrbytes));
	}

	return;
}
