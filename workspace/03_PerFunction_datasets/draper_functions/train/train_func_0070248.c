az6007_ci_slot_ts_enable(struct dvb_ca_en50221 *ca, int slot)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);

	int ret;
	u8 req;
	u16 value;
	u16 index;
	int blen;

	pr_debug("%s()\n", __func__);
	mutex_lock(&state->ca_mutex);
	req = 0xC7;
	value = 1;
	index = 0;
	blen = 0;

	ret = az6007_write(d, req, value, index, NULL, blen);
	if (ret != 0) {
		pr_warn("usb out operation failed. (%d)\n", ret);
		goto failed;
	}

failed:
	mutex_unlock(&state->ca_mutex);
	return ret;
}
