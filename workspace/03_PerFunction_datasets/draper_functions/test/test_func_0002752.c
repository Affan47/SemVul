hns_ppe_common_get_ioaddr(
	struct ppe_common_cb *ppe_common)
{
	void __iomem *base_addr;

	int idx = ppe_common->comm_index;

	if (idx == HNS_DSAF_COMM_SERVICE_NW_IDX)
		base_addr = ppe_common->dsaf_dev->ppe_base
			+ PPE_COMMON_REG_OFFSET;
	else
		base_addr = ppe_common->dsaf_dev->sds_base
			+ (idx - 1) * HNS_DSAF_DEBUG_NW_REG_OFFSET
			+ PPE_COMMON_REG_OFFSET;

	return base_addr;
}
