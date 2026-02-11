ndev_db_addr(struct intel_ntb_dev *ndev,
			       phys_addr_t *db_addr, resource_size_t *db_size,
			       phys_addr_t reg_addr, unsigned long reg)
{
	if (ndev_is_unsafe(ndev, NTB_UNSAFE_DB))
		pr_warn_once("%s: NTB unsafe doorbell access", __func__);

	if (db_addr) {
		*db_addr = reg_addr + reg;
		dev_dbg(ndev_dev(ndev), "Peer db addr %llx\n", *db_addr);
	}

	if (db_size) {
		*db_size = ndev->reg->db_size;
		dev_dbg(ndev_dev(ndev), "Peer db size %llx\n", *db_size);
	}

	return 0;
}
