wdt87xx_ts_interrupt(int irq, void *dev_id)
{
	struct wdt87xx_data *wdt = dev_id;
	struct i2c_client *client = wdt->client;
	int i, fingers;
	int error;
	u8 raw_buf[WDT_V1_RAW_BUF_COUNT] = {0};

	error = i2c_master_recv(client, raw_buf, WDT_V1_RAW_BUF_COUNT);
	if (error < 0) {
		dev_err(&client->dev, "read v1 raw data failed: %d\n", error);
		goto irq_exit;
	}

	fingers = raw_buf[TOUCH_PK_V1_OFFSET_FNGR_NUM];
	if (!fingers)
		goto irq_exit;

	for (i = 0; i < WDT_MAX_FINGER; i++)
		wdt87xx_report_contact(wdt->input,
				       &wdt->param,
				       &raw_buf[TOUCH_PK_V1_OFFSET_EVENT +
						i * FINGER_EV_V1_SIZE]);

	input_mt_sync_frame(wdt->input);
	input_sync(wdt->input);

irq_exit:
	return IRQ_HANDLED;
}
