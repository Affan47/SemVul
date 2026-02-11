build_setup_frame_hash(u16 *setup_frm, struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	u16 hash_table[32];
	struct netdev_hw_addr *ha;
	int i;
	u16 *eaddrs;

	memset(hash_table, 0, sizeof(hash_table));
	__set_bit_le(255, hash_table);

	netdev_for_each_mc_addr(ha, dev) {
		int index = ether_crc_le(ETH_ALEN, ha->addr) & 0x1ff;

		__set_bit_le(index, hash_table);
	}

	for (i = 0; i < 32; i++) {
		*setup_frm++ = hash_table[i];
		*setup_frm++ = hash_table[i];
	}
	setup_frm = &de->setup_frame[13*6];


	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
}
