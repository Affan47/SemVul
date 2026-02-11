wl1273_fm_start(struct wl1273_device *radio, int new_mode)
{
	struct wl1273_core *core = radio->core;
	struct wl1273_fm_platform_data *pdata = core->pdata;
	struct device *dev = radio->dev;
	int r = -EINVAL;

	if (pdata->enable && core->mode == WL1273_MODE_OFF) {
		dev_dbg(radio->dev, "Out of reset\n");

		pdata->enable();
		msleep(250);
	}

	if (new_mode == WL1273_MODE_RX) {
		u16 val = WL1273_POWER_SET_FM;

		if (radio->rds_on)
			val |= WL1273_POWER_SET_RDS;


		r = core->write(core, WL1273_POWER_SET, val);
		if (r) {
			msleep(100);

			r = core->write(core, WL1273_POWER_SET, val);
			if (r) {
				dev_err(dev, "%s: POWER_SET fails\n", __func__);
				goto fail;
			}
		}


		radio->wr_index = 0;
		radio->rd_index = 0;

	} else if (new_mode == WL1273_MODE_TX) {

		r = core->write(core, WL1273_PUPD_SET, WL1273_PUPD_SET_ON);
		if (r) {
			msleep(100);
			r = core->write(core, WL1273_PUPD_SET,
					WL1273_PUPD_SET_ON);
			if (r) {
				dev_err(dev, "%s: PUPD_SET fails\n", __func__);
				goto fail;
			}
		}

		if (radio->rds_on)
			r = core->write(core, WL1273_RDS_DATA_ENB, 1);
		else
			r = core->write(core, WL1273_RDS_DATA_ENB, 0);
	} else {
		dev_warn(dev, "%s: Illegal mode.\n", __func__);
	}

	if (core->mode == WL1273_MODE_OFF) {
		r = wl1273_fm_upload_firmware_patch(radio);
		if (r)
			dev_warn(dev, "Firmware upload failed.\n");


		if (new_mode == WL1273_MODE_RX) {
			u16 val = WL1273_POWER_SET_FM;

			if (radio->rds_on)
				val |= WL1273_POWER_SET_RDS;

			r = core->write(core, WL1273_POWER_SET, val);
			if (r) {
				dev_err(dev, "%s: POWER_SET fails\n", __func__);
				goto fail;
			}
		} else if (new_mode == WL1273_MODE_TX) {
			r = core->write(core, WL1273_PUPD_SET,
					WL1273_PUPD_SET_ON);
			if (r) {
				dev_err(dev, "%s: PUPD_SET fails\n", __func__);
				goto fail;
			}
		}
	}

	return 0;
fail:
	if (pdata->disable)
		pdata->disable();

	dev_dbg(dev, "%s: return: %d\n", __func__, r);
	return r;
}
