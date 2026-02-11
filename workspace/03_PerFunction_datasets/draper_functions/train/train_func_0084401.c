wl1273_fm_tx_set_spacing(struct wl1273_device *radio,
				    unsigned int spacing)
{
	struct wl1273_core *core = radio->core;
	int r;

	if (spacing == 0) {
		r = core->write(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_100kHz);
		radio->spacing = 100;
	} else if (spacing - 50000 < 25000) {
		r = core->write(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_50kHz);
		radio->spacing = 50;
	} else if (spacing - 100000 < 50000) {
		r = core->write(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_100kHz);
		radio->spacing = 100;
	} else {
		r = core->write(core, WL1273_SCAN_SPACING_SET,
				WL1273_SPACING_200kHz);
		radio->spacing = 200;
	}

	return r;
}
