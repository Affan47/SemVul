sis190_mii_probe_88e1111_fixup(struct sis190_private *tp)
{
	if (tp->features & F_PHY_88E1111) {
		void __iomem *ioaddr = tp->mmio_addr;
		int phy_id = tp->mii_if.phy_id;
		u16 reg[2][2] = {
			{ 0x808b, 0x0ce1 },
			{ 0x808f, 0x0c60 }
		}, *p;

		p = (tp->features & F_HAS_RGMII) ? reg[0] : reg[1];

		mdio_write(ioaddr, phy_id, 0x1b, p[0]);
		udelay(200);
		mdio_write(ioaddr, phy_id, 0x14, p[1]);
		udelay(200);
	}
}
