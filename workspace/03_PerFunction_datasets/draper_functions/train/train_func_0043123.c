nes_netdev_set_mac_address(struct net_device *netdev, void *p)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct sockaddr *mac_addr = p;
	int i;
	u32 macaddr_low;
	u16 macaddr_high;

	if (!is_valid_ether_addr(mac_addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(netdev->dev_addr, mac_addr->sa_data, netdev->addr_len);
	printk(PFX "%s: Address length = %d, Address = %pM\n",
	       __func__, netdev->addr_len, mac_addr->sa_data);
	macaddr_high  = ((u16)netdev->dev_addr[0]) << 8;
	macaddr_high += (u16)netdev->dev_addr[1];
	macaddr_low   = ((u32)netdev->dev_addr[2]) << 24;
	macaddr_low  += ((u32)netdev->dev_addr[3]) << 16;
	macaddr_low  += ((u32)netdev->dev_addr[4]) << 8;
	macaddr_low  += (u32)netdev->dev_addr[5];

	for (i = 0; i < NES_MAX_PORT_COUNT; i++) {
		if (nesvnic->qp_nic_index[i] == 0xf) {
			break;
		}
		nes_write_indexed(nesdev,
				NES_IDX_PERFECT_FILTER_LOW + (nesvnic->qp_nic_index[i] * 8),
				macaddr_low);
		nes_write_indexed(nesdev,
				NES_IDX_PERFECT_FILTER_HIGH + (nesvnic->qp_nic_index[i] * 8),
				(u32)macaddr_high | NES_MAC_ADDR_VALID |
				((((u32)nesvnic->nic_index) << 16)));
	}
	return 0;
}
