enic_dev_open(struct enic *enic)
{
	int err;

	err = enic_dev_wait(enic->vdev, vnic_dev_open,
		vnic_dev_open_done, 0);
	if (err)
		dev_err(enic_get_dev(enic), "vNIC device open failed, err %d\n",
			err);

	return err;
}
