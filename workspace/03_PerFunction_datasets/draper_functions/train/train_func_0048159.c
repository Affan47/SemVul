cnic_set_bnx2_mac(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	u32 val;

	val = cp->func << 2;

	cp->shmem_base = cnic_reg_rd_ind(dev, BNX2_SHM_HDR_ADDR_0 + val);

	val = cnic_reg_rd_ind(dev, cp->shmem_base +
			      BNX2_PORT_HW_CFG_ISCSI_MAC_UPPER);
	dev->mac_addr[0] = (u8) (val >> 8);
	dev->mac_addr[1] = (u8) val;

	CNIC_WR(dev, BNX2_EMAC_MAC_MATCH4, val);

	val = cnic_reg_rd_ind(dev, cp->shmem_base +
			      BNX2_PORT_HW_CFG_ISCSI_MAC_LOWER);
	dev->mac_addr[2] = (u8) (val >> 24);
	dev->mac_addr[3] = (u8) (val >> 16);
	dev->mac_addr[4] = (u8) (val >> 8);
	dev->mac_addr[5] = (u8) val;

	CNIC_WR(dev, BNX2_EMAC_MAC_MATCH5, val);

	val = 4 | BNX2_RPM_SORT_USER2_BC_EN;
	if (BNX2_CHIP(cp) != BNX2_CHIP_5709)
		val |= BNX2_RPM_SORT_USER2_PROM_VLAN;

	CNIC_WR(dev, BNX2_RPM_SORT_USER2, 0x0);
	CNIC_WR(dev, BNX2_RPM_SORT_USER2, val);
	CNIC_WR(dev, BNX2_RPM_SORT_USER2, val | BNX2_RPM_SORT_USER2_ENA);
}
