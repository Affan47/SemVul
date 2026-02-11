skge_link_up(struct skge_port *skge)
{
	skge_write8(skge->hw, SK_REG(skge->port, LNK_LED_REG),
		    LED_BLK_OFF|LED_SYNC_OFF|LED_ON);

	netdev_link_up(skge->netdev);

	DBG2(PFX "%s: Link is up at %d Mbps, %s duplex\n",
	     skge->netdev->name, skge->speed,
	     skge->duplex == DUPLEX_FULL ? "full" : "half");
}
