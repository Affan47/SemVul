mv88e6060_phy_write(struct dsa_switch *ds, int port, int regnum, u16 val)
{
	int addr;

	addr = mv88e6060_port_to_phy_addr(port);
	if (addr == -1)
		return 0xffff;

	return reg_write(ds, addr, regnum, val);
}
