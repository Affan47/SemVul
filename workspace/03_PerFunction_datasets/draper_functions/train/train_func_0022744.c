adf_dev_aer_schedule_reset(struct adf_accel_dev *accel_dev,
				      enum adf_dev_reset_mode mode)
{
	struct adf_reset_dev_data *reset_data;

	if (!adf_dev_started(accel_dev) ||
	    test_bit(ADF_STATUS_RESTARTING, &accel_dev->status))
		return 0;

	set_bit(ADF_STATUS_RESTARTING, &accel_dev->status);
	reset_data = kzalloc(sizeof(*reset_data), GFP_ATOMIC);
	if (!reset_data)
		return -ENOMEM;
	reset_data->accel_dev = accel_dev;
	init_completion(&reset_data->compl);
	reset_data->mode = mode;
	INIT_WORK(&reset_data->reset_work, adf_device_reset_worker);
	queue_work(device_reset_wq, &reset_data->reset_work);


	if (mode == ADF_DEV_RESET_SYNC) {
		int ret = 0;

		unsigned long wait_jiffies = msecs_to_jiffies(10000);
		unsigned long timeout = wait_for_completion_timeout(
				   &reset_data->compl, wait_jiffies);
		if (!timeout) {
			dev_err(&GET_DEV(accel_dev),
				"Reset device timeout expired\n");
			ret = -EFAULT;
		}
		kfree(reset_data);
		return ret;
	}
	return 0;
}
