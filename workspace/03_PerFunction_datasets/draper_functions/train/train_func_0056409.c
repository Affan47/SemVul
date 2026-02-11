mv88e1xxx_phy_create(struct net_device *dev, int phy_addr,
					 const struct mdio_ops *mdio_ops)
{
	struct adapter *adapter = netdev_priv(dev);
	struct cphy *cphy = kzalloc(sizeof(*cphy), GFP_KERNEL);

	if (!cphy)
		return NULL;

	cphy_init(cphy, dev, phy_addr, &mv88e1xxx_ops, mdio_ops);


	if ((board_info(adapter)->caps & SUPPORTED_TP) &&
	    board_info(adapter)->chip_phy == CHBT_PHY_88E1111) {


		(void) simple_mdio_write(cphy,
				MV88E1XXX_EXTENDED_ADDR_REGISTER, 0xB);
		(void) simple_mdio_write(cphy,
				MV88E1XXX_EXTENDED_REGISTER, 0x8004);
	}
	(void) mv88e1xxx_downshift_set(cphy, 1);


	if (is_T2(adapter)) {
		(void) simple_mdio_write(cphy,
				MV88E1XXX_LED_CONTROL_REGISTER, 0x1);
	}

	return cphy;
}
