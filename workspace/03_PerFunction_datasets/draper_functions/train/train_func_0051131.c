link_start(struct port_info *p)
{
	struct cmac *mac = p->mac;

	mac->ops->reset(mac);
	if (mac->ops->macaddress_set)
		mac->ops->macaddress_set(mac, p->dev->dev_addr);
	t1_set_rxmode(p->dev);
	t1_link_start(p->phy, mac, &p->link_config);
	mac->ops->enable(mac, MAC_DIRECTION_RX | MAC_DIRECTION_TX);
}
