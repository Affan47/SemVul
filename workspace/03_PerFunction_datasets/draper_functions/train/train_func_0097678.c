wacom_i2c_irq(int irq, void *dev_id)
{
	struct wacom_i2c *wac_i2c = dev_id;
	struct input_dev *input = wac_i2c->input;
	u8 *data = wac_i2c->data;
	unsigned int x, y, pressure;
	unsigned char tsw, f1, f2, ers;
	int error;

	error = i2c_master_recv(wac_i2c->client,
				wac_i2c->data, sizeof(wac_i2c->data));
	if (error < 0)
		goto out;

	tsw = data[3] & 0x01;
	ers = data[3] & 0x04;
	f1 = data[3] & 0x02;
	f2 = data[3] & 0x10;
	x = le16_to_cpup((__le16 *)&data[4]);
	y = le16_to_cpup((__le16 *)&data[6]);
	pressure = le16_to_cpup((__le16 *)&data[8]);

	if (!wac_i2c->prox)
		wac_i2c->tool = (data[3] & 0x0c) ?
			BTN_TOOL_RUBBER : BTN_TOOL_PEN;

	wac_i2c->prox = data[3] & 0x20;

	input_report_key(input, BTN_TOUCH, tsw || ers);
	input_report_key(input, wac_i2c->tool, wac_i2c->prox);
	input_report_key(input, BTN_STYLUS, f1);
	input_report_key(input, BTN_STYLUS2, f2);
	input_report_abs(input, ABS_X, x);
	input_report_abs(input, ABS_Y, y);
	input_report_abs(input, ABS_PRESSURE, pressure);
	input_sync(input);

out:
	return IRQ_HANDLED;
}
