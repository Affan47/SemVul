cnic_ring_ctl(struct cnic_dev *dev, u32 cid, u32 cl_id, int start)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct cnic_eth_dev *ethdev = cp->ethdev;
	struct drv_ctl_info info;
	struct drv_ctl_l2_ring *ring = &info.data.ring;

	memset(&info, 0, sizeof(struct drv_ctl_info));
	if (start)
		info.cmd = DRV_CTL_START_L2_CMD;
	else
		info.cmd = DRV_CTL_STOP_L2_CMD;

	ring->cid = cid;
	ring->client_id = cl_id;
	ethdev->drv_ctl(dev->netdev, &info);
}
