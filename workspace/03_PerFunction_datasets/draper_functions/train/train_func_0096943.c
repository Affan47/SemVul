dm9132_id_table(struct net_device *dev)
{
	struct dmfe_board_info *db = netdev_priv(dev);
	void __iomem *ioaddr = db->ioaddr + 0xc0;
	u16 *addrptr = (u16 *)dev->dev_addr;
	struct netdev_hw_addr *ha;
	u16 i, hash_table[4];


	for (i = 0; i < 3; i++) {
		dw16(0, addrptr[i]);
		ioaddr += 4;
	}


	memset(hash_table, 0, sizeof(hash_table));


	hash_table[3] = 0x8000;


	netdev_for_each_mc_addr(ha, dev) {
		u32 hash_val = cal_CRC((char *)ha->addr, 6, 0) & 0x3f;

		hash_table[hash_val / 16] |= (u16) 1 << (hash_val % 16);
	}


	for (i = 0; i < 4; i++, ioaddr += 4)
		dw16(0, hash_table[i]);
}
