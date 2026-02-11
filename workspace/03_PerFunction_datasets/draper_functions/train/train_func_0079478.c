sensor_hub_remove_callback(struct hid_sensor_hub_device *hsdev,
				u32 usage_id)
{
	struct hid_sensor_hub_callbacks_list *callback;
	struct sensor_hub_data *pdata = hid_get_drvdata(hsdev->hdev);
	unsigned long flags;

	spin_lock_irqsave(&pdata->dyn_callback_lock, flags);
	list_for_each_entry(callback, &pdata->dyn_callback_list, list)
		if (callback->usage_id == usage_id &&
						callback->hsdev == hsdev) {
			list_del(&callback->list);
			kfree(callback);
			break;
		}
	spin_unlock_irqrestore(&pdata->dyn_callback_lock, flags);

	return 0;
}
