suggest_mac_setup(void)
{
	char buf[128];
	unsigned char buf_mac[ETH_ALEN];

	sprintf_eth_mac(buf, __suggest_mac);
	if (menu_choose_mac("suggest MAC base", buf_mac, buf) < 0)
		return;
	memcpy(__suggest_mac, buf_mac, sizeof(buf_mac));
}
