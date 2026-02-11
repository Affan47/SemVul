sensor_hub_remove(struct hid_device *hdev)
{
	struct sensor_hub_data *data = hid_get_drvdata(hdev);
	unsigned long flags;
	int i;

	hid_dbg(hdev, " hardware removed\n");
	hid_hw_close(hdev);
	hid_hw_stop(hdev);
	spin_lock_irqsave(&data->lock, flags);
	for (i = 0; i < data->hid_sensor_client_cnt; ++i) {
		struct hid_sensor_hub_device *hsdev =
			data->hid_sensor_hub_client_devs[i].platform_data;
		if (hsdev->pending.status)
			complete(&hsdev->pending.ready);
	}
	spin_unlock_irqrestore(&data->lock, flags);
	mfd_remove_devices(&hdev->dev);
	hid_set_drvdata(hdev, NULL);
	mutex_destroy(&data->mutex);
}
