i2400m_reset(struct i2400m *i2400m, enum i2400m_reset_type rt)
{
	struct net_device *net_dev = i2400m->wimax_dev.net_dev;


	if (net_dev->reg_state == NETREG_REGISTERED) {
		netif_tx_disable(net_dev);
		netif_carrier_off(net_dev);
	}
	return i2400m->bus_reset(i2400m, rt);
}
