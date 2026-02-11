cnic_alloc_dev(struct net_device *dev,
				       struct pci_dev *pdev)
{
	struct cnic_dev *cdev;
	struct cnic_local *cp;
	int alloc_size;

	alloc_size = sizeof(struct cnic_dev) + sizeof(struct cnic_local);

	cdev = kzalloc(alloc_size, GFP_KERNEL);
	if (cdev == NULL)
		return NULL;

	cdev->netdev = dev;
	cdev->cnic_priv = (char *)cdev + sizeof(struct cnic_dev);
	cdev->register_device = cnic_register_device;
	cdev->unregister_device = cnic_unregister_device;
	cdev->iscsi_nl_msg_recv = cnic_iscsi_nl_msg_recv;
	cdev->get_fc_npiv_tbl = cnic_get_fc_npiv_tbl;

	cp = cdev->cnic_priv;
	cp->dev = cdev;
	cp->l2_single_buf_size = 0x400;
	cp->l2_rx_ring_size = 3;

	spin_lock_init(&cp->cnic_ulp_lock);

	netdev_info(dev, "Added CNIC device\n");

	return cdev;
}
