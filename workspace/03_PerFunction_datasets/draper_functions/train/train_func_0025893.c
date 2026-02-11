edt_ft5x06_ts_isr(int irq, void *dev_id)
{
	struct edt_ft5x06_ts_data *tsdata = dev_id;
	struct device *dev = &tsdata->client->dev;
	u8 cmd;
	u8 rdbuf[63];
	int i, type, x, y, id;
	int offset, tplen, datalen, crclen;
	int error;

	switch (tsdata->version) {
	case M06:
		cmd = 0xf9;
		offset = 5;
		tplen = 4;
		crclen = 1;
		break;

	case M09:
		cmd = 0x0;
		offset = 3;
		tplen = 6;
		crclen = 0;
		break;

	default:
		goto out;
	}

	memset(rdbuf, 0, sizeof(rdbuf));
	datalen = tplen * tsdata->max_support_points + offset + crclen;

	error = edt_ft5x06_ts_readwrite(tsdata->client,
					sizeof(cmd), &cmd,
					datalen, rdbuf);
	if (error) {
		dev_err_ratelimited(dev, "Unable to fetch data, error: %d\n",
				    error);
		goto out;
	}


	if (tsdata->version == M06) {
		if (rdbuf[0] != 0xaa || rdbuf[1] != 0xaa ||
			rdbuf[2] != datalen) {
			dev_err_ratelimited(dev,
					"Unexpected header: %02x%02x%02x!\n",
					rdbuf[0], rdbuf[1], rdbuf[2]);
			goto out;
		}

		if (!edt_ft5x06_ts_check_crc(tsdata, rdbuf, datalen))
			goto out;
	}

	for (i = 0; i < tsdata->max_support_points; i++) {
		u8 *buf = &rdbuf[i * tplen + offset];
		bool down;

		type = buf[0] >> 6;

		if (type == TOUCH_EVENT_RESERVED)
			continue;


		if (tsdata->version == M06 && type == TOUCH_EVENT_DOWN)
			continue;

		x = ((buf[0] << 8) | buf[1]) & 0x0fff;
		y = ((buf[2] << 8) | buf[3]) & 0x0fff;
		id = (buf[2] >> 4) & 0x0f;
		down = type != TOUCH_EVENT_UP;

		input_mt_slot(tsdata->input, id);
		input_mt_report_slot_state(tsdata->input, MT_TOOL_FINGER, down);

		if (!down)
			continue;

		input_report_abs(tsdata->input, ABS_MT_POSITION_X, x);
		input_report_abs(tsdata->input, ABS_MT_POSITION_Y, y);
	}

	input_mt_report_pointer_emulation(tsdata->input, true);
	input_sync(tsdata->input);

out:
	return IRQ_HANDLED;
}
