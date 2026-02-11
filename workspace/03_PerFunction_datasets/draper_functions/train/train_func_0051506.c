read_mac_address(struct net_device *ndev, unsigned char *mac)
{
	if (mac[0] || mac[1] || mac[2] || mac[3] || mac[4] || mac[5]) {
		memcpy(ndev->dev_addr, mac, ETH_ALEN);
	} else {
		ndev->dev_addr[0] = (sh_eth_read(ndev, MAHR) >> 24);
		ndev->dev_addr[1] = (sh_eth_read(ndev, MAHR) >> 16) & 0xFF;
		ndev->dev_addr[2] = (sh_eth_read(ndev, MAHR) >> 8) & 0xFF;
		ndev->dev_addr[3] = (sh_eth_read(ndev, MAHR) & 0xFF);
		ndev->dev_addr[4] = (sh_eth_read(ndev, MALR) >> 8) & 0xFF;
		ndev->dev_addr[5] = (sh_eth_read(ndev, MALR) & 0xFF);
	}
}
