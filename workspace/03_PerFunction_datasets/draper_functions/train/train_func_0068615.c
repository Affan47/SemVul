vnic_dev_hang_reset(struct vnic_dev *vdev, int arg)
{
	u64 a0 = (u32)arg, a1 = 0;
	int wait = 1000;
	int err;

	if (vnic_dev_capable(vdev, CMD_HANG_RESET)) {
		return vnic_dev_cmd(vdev, CMD_HANG_RESET,
				&a0, &a1, wait);
	} else {
		err = vnic_dev_soft_reset(vdev, arg);
		if (err)
			return err;
		return vnic_dev_init(vdev, 0);
	}
}
