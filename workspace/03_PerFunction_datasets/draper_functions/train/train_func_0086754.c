ndev_spad_write(struct intel_ntb_dev *ndev, int idx, u32 val,
				  void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_SPAD))
		pr_warn_once("%s: NTB unsafe scratchpad access", __func__);

	if (idx < 0 || idx >= ndev->spad_count)
		return -EINVAL;

	iowrite32(val, mmio + (idx << 2));

	return 0;
}
