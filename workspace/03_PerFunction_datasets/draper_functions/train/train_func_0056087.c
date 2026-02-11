amd_ntb_peer_spad_read(struct ntb_dev *ntb, int idx)
{
	struct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->self_mmio;
	u32 offset;

	if (idx < 0 || idx >= ndev->spad_count)
		return -EINVAL;

	offset = ndev->peer_spad + (idx << 2);
	return readl(mmio + AMD_SPAD_OFFSET + offset);
}
