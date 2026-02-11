vnic_dev_notify_set(struct vnic_dev *vdev, u16 intr)
{
	void *notify_addr;
	dma_addr_t notify_pa;

	if (vdev->notify || vdev->notify_pa) {
		vdev_neterr("notify block %p still allocated", vdev->notify);
		return -EINVAL;
	}

	notify_addr = pci_alloc_consistent(vdev->pdev,
			sizeof(struct vnic_devcmd_notify),
			&notify_pa);
	if (!notify_addr)
		return -ENOMEM;

	return vnic_dev_notify_setcmd(vdev, notify_addr, notify_pa, intr);
}
