rtl8102e_hw_phy_config(void *ioaddr)
{
	struct phy_reg phy_reg_init[] = {
		{ 0x1f, 0x0003 },
		{ 0x08, 0x441d },
		{ 0x01, 0x9100 },
		{ 0x1f, 0x0000 }
	};

	DBGP ( "rtl8102e_hw_phy_config\n" );

	mdio_write(ioaddr, 0x1f, 0x0000);
	mdio_patch(ioaddr, 0x11, 1 << 12);
	mdio_patch(ioaddr, 0x19, 1 << 13);

	rtl_phy_write(ioaddr, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}
