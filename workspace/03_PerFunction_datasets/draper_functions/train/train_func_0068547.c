ndev_db_write(struct intel_ntb_dev *ndev, u64 db_bits,
				void __iomem *mmio)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	if (db_bits & ~ndev->db_valid_mask)
		return -EINVAL;

	ndev->reg->db_iowrite(db_bits, mmio);

	return 0;
}
