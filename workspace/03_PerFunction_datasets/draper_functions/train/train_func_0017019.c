wl1273_fm_set_rds(struct wl1273_device *radio, unsigned int new_mode)
{
	int r = 0;
	struct wl1273_core *core = radio->core;

	if (core->mode == WL1273_MODE_OFF ||
	    core->mode == WL1273_MODE_SUSPENDED)
		return -EPERM;

	if (new_mode == WL1273_RDS_RESET) {
		r = core->write(core, WL1273_RDS_CNTRL_SET, 1);
		return r;
	}

	if (core->mode == WL1273_MODE_TX && new_mode == WL1273_RDS_OFF) {
		r = core->write(core, WL1273_RDS_DATA_ENB, 0);
	} else if (core->mode == WL1273_MODE_TX && new_mode == WL1273_RDS_ON) {
		r = core->write(core, WL1273_RDS_DATA_ENB, 1);
	} else if (core->mode == WL1273_MODE_RX && new_mode == WL1273_RDS_OFF) {
		r = wl1273_fm_rds_off(radio);
	} else if (core->mode == WL1273_MODE_RX && new_mode == WL1273_RDS_ON) {
		r = wl1273_fm_rds_on(radio);
	} else {
		dev_err(radio->dev, "%s: Unknown mode: %d\n",
			__func__, new_mode);
		r = -EINVAL;
	}

	if (!r)
		radio->rds_on = (new_mode == WL1273_RDS_ON) ? true : false;

	return r;
}
