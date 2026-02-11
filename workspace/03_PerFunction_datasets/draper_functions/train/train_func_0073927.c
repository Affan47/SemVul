qla82xx_pci_is_same_window(struct qla_hw_data *ha,
	unsigned long long addr)
{
	int			window;
	unsigned long long	qdr_max;

	qdr_max = QLA82XX_P3_ADDR_QDR_NET_MAX;


	if (addr_in_range(addr, QLA82XX_ADDR_DDR_NET,
		QLA82XX_ADDR_DDR_NET_MAX))
		BUG();
	else if (addr_in_range(addr, QLA82XX_ADDR_OCM0,
		QLA82XX_ADDR_OCM0_MAX))
		return 1;
	else if (addr_in_range(addr, QLA82XX_ADDR_OCM1,
		QLA82XX_ADDR_OCM1_MAX))
		return 1;
	else if (addr_in_range(addr, QLA82XX_ADDR_QDR_NET, qdr_max)) {

		window = ((addr - QLA82XX_ADDR_QDR_NET) >> 22) & 0x3f;
		if (ha->qdr_sn_window == window)
			return 1;
	}
	return 0;
}
