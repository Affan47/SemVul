mac_disable(struct cmac *mac, int which)
{
	u32 val;
	int i, port = mac->instance->index;


	mac_reset(mac);

	vsc_read(mac->adapter, REG_MODE_CFG(port), &val);
	if (which & MAC_DIRECTION_RX)
		val &= ~0x2;
	if (which & MAC_DIRECTION_TX)
		val &= ~0x1;
	vsc_write(mac->adapter, REG_MODE_CFG(port), val);
	vsc_read(mac->adapter, REG_MODE_CFG(port), &val);


	for (i = 0; i <= 0x3a; ++i)
		vsc_write(mac->adapter, CRA(4, port, i), 0);


	memset(&mac->stats, 0, sizeof(struct cmac_statistics));

	return 0;
}
