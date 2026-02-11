si4713_wait_stc(struct si4713_device *sdev, const int usecs)
{
	struct i2c_client *client = v4l2_get_subdevdata(&sdev->sd);
	u8 resp[SI4713_GET_STATUS_NRESP];
	unsigned long start_jiffies = jiffies;
	int err;

	if (client->irq &&
	    !wait_for_completion_timeout(&sdev->work, usecs_to_jiffies(usecs) + 1))
		v4l2_warn(&sdev->sd,
			"(%s) Device took too much time to answer.\n", __func__);

	for (;;) {

		err = si4713_send_command(sdev, SI4713_CMD_GET_INT_STATUS,
				NULL, 0,
				resp, ARRAY_SIZE(resp),
				DEFAULT_TIMEOUT);


		if (err >= 0) {
			v4l2_dbg(1, debug, &sdev->sd,
				"%s: status bits: 0x%02x\n", __func__, resp[0]);

			if (resp[0] & SI4713_STC_INT)
				return 0;
		}
		if (jiffies_to_usecs(jiffies - start_jiffies) > usecs)
			return err < 0 ? err : -EIO;


		usleep_range(3000, 4000);
	}
}
