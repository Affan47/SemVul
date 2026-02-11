mdio_read(struct nic *nic __unused, int phy_id, int reg_num)
{
	u16 val_out;
	int phyaddr;

	if (!lp->mii)
		return 0;

	phyaddr = lp->a.read_bcr(ioaddr, 33);

	lp->a.write_bcr(ioaddr, 33,
			((phy_id & 0x1f) << 5) | (reg_num & 0x1f));
	val_out = lp->a.read_bcr(ioaddr, 34);
	lp->a.write_bcr(ioaddr, 33, phyaddr);

	return val_out;
}
