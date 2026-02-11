atl1_get_regs(struct net_device *netdev, struct ethtool_regs *regs,
	void *p)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_hw *hw = &adapter->hw;
	unsigned int i;
	u32 *regbuf = p;

	for (i = 0; i < ATL1_REG_COUNT; i++) {


		switch (i) {
		case 6 ... 9:
		case 14:
		case 29 ... 31:
		case 34 ... 63:
		case 75 ... 127:
		case 136 ... 1023:
		case 1027 ... 1087:
		case 1091 ... 1151:
		case 1194 ... 1195:
		case 1200 ... 1201:
		case 1206 ... 1213:
		case 1216 ... 1279:
		case 1290 ... 1311:
		case 1323 ... 1343:
		case 1358 ... 1359:
		case 1368 ... 1375:
		case 1378 ... 1383:
		case 1388 ... 1391:
		case 1393 ... 1395:
		case 1402 ... 1403:
		case 1410 ... 1471:
		case 1522 ... 1535:

			regbuf[i] = 0;
			break;
		default:

			regbuf[i] = ioread32(hw->hw_addr + (i * sizeof(u32)));
		}
	}
}
