si4713_send_command(struct si4713_device *sdev, const u8 command,
				const u8 args[], const int argn,
				u8 response[], const int respn, const int usecs)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	unsigned long until_jiffies;
	u8 data1[MAX_ARGS + 1];
	int err;

	if (!client->adapter)
		return -ENODEV;


	data1[0] = command;
	memcpy(data1 + 1, args, argn);
	DBG_BUFFER(&sdev->sd, "Parameters", data1, argn + 1);

	err = i2c_master_send(client, data1, argn + 1);
	if (err != argn + 1) {
		v4l2_err(&sdev->sd, "Error while sending command 0x%02x\n",
			command);
		return err < 0 ? err : -EIO;
	}

	until_jiffies = jiffies + usecs_to_jiffies(usecs) + 1;


	if (client->irq) {
		if (!wait_for_completion_timeout(&sdev->work,
				usecs_to_jiffies(usecs) + 1))
			v4l2_warn(&sdev->sd,
				"(%s) Device took too much time to answer.\n",
				__func__);
	}

	do {
		err = i2c_master_recv(client, response, respn);
		if (err != respn) {
			v4l2_err(&sdev->sd,
				"Error %d while reading response for command 0x%02x\n",
				err, command);
			return err < 0 ? err : -EIO;
		}

		DBG_BUFFER(&sdev->sd, "Response", response, respn);
		if (!check_command_failed(response[0]))
			return 0;

		if (client->irq)
			return -EBUSY;
		if (usecs <= 1000)
			usleep_range(usecs, 1000);
		else
			usleep_range(1000, 2000);
	} while (time_is_after_jiffies(until_jiffies));

	return -EBUSY;
}
