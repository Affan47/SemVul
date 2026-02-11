amd_ntb_db_clear_mask(struct ntb_dev *ntb, u64 db_bits)
{
	struct amd_ntb_dev *ndev = ntb_ndev(ntb);
	void __iomem *mmio = ndev->self_mmio;
	unsigned long flags;

	if (db_bits & ~ndev->db_valid_mask)
		return -EINVAL;

	spin_lock_irqsave(&ndev->db_mask_lock, flags);
	ndev->db_mask &= ~db_bits;
	writew((u16)ndev->db_mask, mmio + AMD_DBMASK_OFFSET);
	spin_unlock_irqrestore(&ndev->db_mask_lock, flags);

	return 0;
}
