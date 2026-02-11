sky2_link_down(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned port = sky2->port;
	u16 reg;

	gm_phy_write(hw, port, PHY_MARV_INT_MASK, 0);

	reg = gma_read16(hw, port, GM_GP_CTRL);
	reg &= ~(GM_GPCR_RX_ENA | GM_GPCR_TX_ENA);
	gma_write16(hw, port, GM_GP_CTRL, reg);

	netif_carrier_off(sky2->netdev);


	sky2_write8(hw, SK_REG(port, LNK_LED_REG), LINKLED_OFF);

	netif_info(sky2, link, sky2->netdev, "Link is down\n");

	sky2_phy_init(hw, port);
}
