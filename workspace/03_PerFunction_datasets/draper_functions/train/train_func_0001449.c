svnic_dev_notify_set(struct vnic_dev *vdev, u16 intr)
{
	u64 a0, a1;
	int wait = VNIC_DVCMD_TMO;

	if (!vdev->notify) {
		vdev->notify = pci_alloc_consistent(vdev->pdev,
			sizeof(struct vnic_devcmd_notify),
			&vdev->notify_pa);
		if (!vdev->notify)
			return -ENOMEM;
	}

	a0 = vdev->notify_pa;
	a1 = ((u64)intr << 32) & VNIC_NOTIFY_INTR_MASK;
	a1 += sizeof(struct vnic_devcmd_notify);

	return svnic_dev_cmd(vdev, CMD_NOTIFY, &a0, &a1, wait);
}
