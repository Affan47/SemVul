offload_close(struct t3cdev *tdev)
{
	struct adapter *adapter = tdev2adap(tdev);
	struct t3c_data *td = T3C_DATA(tdev);

	if (!test_bit(OFFLOAD_DEVMAP_BIT, &adapter->open_device_map))
		return 0;


	cxgb3_remove_clients(tdev);

	sysfs_remove_group(&tdev->lldev->dev.kobj, &offload_attr_group);


	flush_work(&td->tid_release_task);

	tdev->lldev = NULL;
	cxgb3_set_dummy_ops(tdev);
	t3_tp_set_offload_mode(adapter, 0);
	clear_bit(OFFLOAD_DEVMAP_BIT, &adapter->open_device_map);

	if (!adapter->open_device_map)
		cxgb_down(adapter, 0);

	cxgb3_offload_deactivate(adapter);
	return 0;
}
