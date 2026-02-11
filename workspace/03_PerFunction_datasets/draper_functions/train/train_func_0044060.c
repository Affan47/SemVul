az6027_ci_uninit(struct dvb_usb_device *d)
{
	struct az6027_device_state *state;

	deb_info("%s", __func__);

	if (NULL == d)
		return;

	state = (struct az6027_device_state *)d->priv;
	if (NULL == state)
		return;

	if (NULL == state->ca.data)
		return;

	dvb_ca_en50221_release(&state->ca);

	memset(&state->ca, 0, sizeof(state->ca));
}
