sh_eth_tsu_write_entry(struct net_device *ndev, void *reg,
				  const u8 *addr)
{
	u32 val;

	val = addr[0] << 24 | addr[1] << 16 | addr[2] << 8 | addr[3];
	iowrite32(val, reg);
	if (sh_eth_tsu_busy(ndev) < 0)
		return -EBUSY;

	val = addr[4] << 8 | addr[5];
	iowrite32(val, reg + 4);
	if (sh_eth_tsu_busy(ndev) < 0)
		return -EBUSY;

	return 0;
}
