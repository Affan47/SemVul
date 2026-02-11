vp_set_status(struct virtio_device *vdev, u8 status)
{
	struct virtio_pci_device *vp_dev = to_vp_device(vdev);

	BUG_ON(status == 0);
	vp_iowrite8(status, &vp_dev->common->device_status);
}
