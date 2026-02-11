__mc33880_set(struct mc33880 *mc, unsigned offset, int value)
{
	if (value)
		mc->port_config |= 1 << offset;
	else
		mc->port_config &= ~(1 << offset);

	return mc33880_write_config(mc);
}
