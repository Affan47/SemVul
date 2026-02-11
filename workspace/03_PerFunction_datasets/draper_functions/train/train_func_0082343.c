dvbsky_usb_generic_rw(struct dvb_usb_device *d,
		u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	int ret;
	struct dvbsky_state *state = d_to_priv(d);

	mutex_lock(&d->usb_mutex);
	if (wlen != 0)
		memcpy(state->obuf, wbuf, wlen);

	ret = dvb_usbv2_generic_rw_locked(d, state->obuf, wlen,
			state->ibuf, rlen);

	if (!ret && (rlen != 0))
		memcpy(rbuf, state->ibuf, rlen);

	mutex_unlock(&d->usb_mutex);
	return ret;
}
