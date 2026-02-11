svnic_dev_link_status(struct vnic_dev *vdev)
{
	if (vdev->linkstatus)
		return *vdev->linkstatus;

	if (!vnic_dev_notify_ready(vdev))
		return 0;

	return vdev->notify_copy.link_state;
}
