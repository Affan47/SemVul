ndev_db_clear_mask(struct intel_ntb_dev *ndev, u64 db_bits,
				     void __iomem *mmio)
{
	unsigned long irqflags;

	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	if (db_bits & ~ndev->db_valid_mask)
		return -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, irqflags);
	{
		ndev->db_mask &= ~db_bits;
		ndev->reg->db_iowrite(ndev->db_mask, mmio);
	}
	spin_unlock_irqrestore(&ndev->db_mask_lock, irqflags);

	return 0;
}
