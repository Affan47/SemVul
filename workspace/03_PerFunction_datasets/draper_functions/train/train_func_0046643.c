drxk_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct az6007_device_state *st = fe_to_priv(fe);
	struct dvb_usb_adapter *adap = fe->sec_priv;
	int status = 0;

	pr_debug("%s: %s\n", __func__, enable ? "enable" : "disable");

	if (!adap || !st)
		return -EINVAL;

	if (enable)
		status = st->gate_ctrl(fe, 1);
	else
		status = st->gate_ctrl(fe, 0);

	return status;
}
