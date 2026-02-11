adf_init_admin_comms(struct adf_accel_dev *accel_dev)
{
	struct adf_admin_comms *admin;
	struct adf_hw_device_data *hw_data = accel_dev->hw_device;
	struct adf_bar *pmisc =
		&GET_BARS(accel_dev)[hw_data->get_misc_bar_id(hw_data)];
	void __iomem *csr = pmisc->virt_addr;
	void __iomem *mailbox = csr + ADF_DH895XCC_MAILBOX_BASE_OFFSET;
	u64 reg_val;

	admin = kzalloc_node(sizeof(*accel_dev->admin), GFP_KERNEL,
			     dev_to_node(&GET_DEV(accel_dev)));
	if (!admin)
		return -ENOMEM;
	admin->virt_addr = dma_zalloc_coherent(&GET_DEV(accel_dev), PAGE_SIZE,
					       &admin->phy_addr, GFP_KERNEL);
	if (!admin->virt_addr) {
		dev_err(&GET_DEV(accel_dev), "Failed to allocate dma buff\n");
		kfree(admin);
		return -ENOMEM;
	}

	admin->const_tbl_addr = dma_map_single(&GET_DEV(accel_dev),
					       (void *) const_tab, 1024,
					       DMA_TO_DEVICE);

	if (unlikely(dma_mapping_error(&GET_DEV(accel_dev),
				       admin->const_tbl_addr))) {
		dma_free_coherent(&GET_DEV(accel_dev), PAGE_SIZE,
				  admin->virt_addr, admin->phy_addr);
		kfree(admin);
		return -ENOMEM;
	}
	reg_val = (u64)admin->phy_addr;
	ADF_CSR_WR(csr, ADF_DH895XCC_ADMINMSGUR_OFFSET, reg_val >> 32);
	ADF_CSR_WR(csr, ADF_DH895XCC_ADMINMSGLR_OFFSET, reg_val);
	mutex_init(&admin->lock);
	admin->mailbox_addr = mailbox;
	accel_dev->admin = admin;
	return 0;
}
