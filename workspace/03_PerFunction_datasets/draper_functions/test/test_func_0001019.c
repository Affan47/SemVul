rtl8168bb_hw_phy_config(void *ioaddr)
{
	struct phy_reg phy_reg_init[] = {
		{ 0x10, 0xf41b },
		{ 0x1f, 0x0000 }
	};

	mdio_write(ioaddr, 0x1f, 0x0001);
	mdio_patch(ioaddr, 0x16, 1 << 0);

	DBGP ( "rtl8168bb_hw_phy_config\n" );

	rtl_phy_write(ioaddr, phy_reg_init, ARRAY_SIZE(phy_reg_init));
}
