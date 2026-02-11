elants_i2c_calibrate(struct elants_data *ts)
{
	struct i2c_client *client = ts->client;
	int ret, error;
	static const u8 w_flashkey[] = { 0x54, 0xC0, 0xE1, 0x5A };
	static const u8 rek[] = { 0x54, 0x29, 0x00, 0x01 };
	static const u8 rek_resp[] = { CMD_HEADER_REK, 0x66, 0x66, 0x66 };

	disable_irq(client->irq);

	ts->state = ELAN_WAIT_RECALIBRATION;
	reinit_completion(&ts->cmd_done);

	elants_i2c_send(client, w_flashkey, sizeof(w_flashkey));
	elants_i2c_send(client, rek, sizeof(rek));

	enable_irq(client->irq);

	ret = wait_for_completion_interruptible_timeout(&ts->cmd_done,
				msecs_to_jiffies(ELAN_CALI_TIMEOUT_MSEC));

	ts->state = ELAN_STATE_NORMAL;

	if (ret <= 0) {
		error = ret < 0 ? ret : -ETIMEDOUT;
		dev_err(&client->dev,
			"error while waiting for calibration to complete: %d\n",
			error);
		return error;
	}

	if (memcmp(rek_resp, ts->cmd_resp, sizeof(rek_resp))) {
		dev_err(&client->dev,
			"unexpected calibration response: %*ph\n",
			(int)sizeof(ts->cmd_resp), ts->cmd_resp);
		return -EINVAL;
	}

	return 0;
}
