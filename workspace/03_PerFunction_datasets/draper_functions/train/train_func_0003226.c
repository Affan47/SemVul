iscsi_iter_destroy_flashnode_conn_fn(struct device *dev, void *data)
{
	if (!iscsi_is_flashnode_conn_dev(dev, NULL))
		return 0;

	return iscsi_destroy_flashnode_conn(iscsi_dev_to_flash_conn(dev));
}
