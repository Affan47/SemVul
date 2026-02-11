efx_farch_filter_sync_rx_mode(struct efx_nic *efx)
{
	struct net_device *net_dev = efx->net_dev;
	struct netdev_hw_addr *ha;
	union efx_multicast_hash *mc_hash = &efx->multicast_hash;
	u32 crc;
	int bit;

	if (!efx_dev_registered(efx))
		return;

	netif_addr_lock_bh(net_dev);

	efx->unicast_filter = !(net_dev->flags & IFF_PROMISC);


	if (net_dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		memset(mc_hash, 0xff, sizeof(*mc_hash));
	} else {
		memset(mc_hash, 0x00, sizeof(*mc_hash));
		netdev_for_each_mc_addr(ha, net_dev) {
			crc = ether_crc_le(ETH_ALEN, ha->addr);
			bit = crc & (EFX_MCAST_HASH_ENTRIES - 1);
			__set_bit_le(bit, mc_hash);
		}


		__set_bit_le(0xff, mc_hash);
	}

	netif_addr_unlock_bh(net_dev);
}
