az6007_ci_write_attribute_mem(struct dvb_ca_en50221 *ca,
					 int slot,
					 int address,
					 u8 value)
{
	struct dvb_usb_device *d = (struct dvb_usb_device *)ca->data;
	struct az6007_device_state *state = d_to_priv(d);

	int ret;
	u8 req;
	u16 value1;
	u16 index;
	int blen;

	pr_debug("%s(), slot %d\n", __func__, slot);
	if (slot != 0)
		return -EINVAL;

	mutex_lock(&state->ca_mutex);
	req = 0xC2;
	value1 = address;
	index = value;
	blen = 0;

	ret = az6007_write(d, req, value1, index, NULL, blen);
	if (ret != 0)
		pr_warn("usb out operation failed. (%d)\n", ret);

	mutex_unlock(&state->ca_mutex);
	return ret;
}
