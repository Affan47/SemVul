vnic_dev_unregister(struct vnic_dev *vdev)
{
	if (vdev) {
		if (vdev->notify)
			pci_free_consistent(vdev->pdev,
				sizeof(struct vnic_devcmd_notify),
				vdev->notify,
				vdev->notify_pa);
		if (vdev->stats)
			pci_free_consistent(vdev->pdev,
				sizeof(struct vnic_stats),
				vdev->stats, vdev->stats_pa);
		if (vdev->fw_info)
			pci_free_consistent(vdev->pdev,
				sizeof(struct vnic_devcmd_fw_info),
				vdev->fw_info, vdev->fw_info_pa);
		if (vdev->devcmd2)
			vnic_dev_deinit_devcmd2(vdev);

		kfree(vdev);
	}
}
