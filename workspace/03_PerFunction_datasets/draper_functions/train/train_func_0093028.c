wm2000_power_down(struct i2c_client *i2c, int analogue)
{
	struct wm2000_priv *wm2000 = dev_get_drvdata(&i2c->dev);

	if (analogue) {
		wm2000_write(i2c, WM2000_REG_ANA_VMID_PD_TIME, 248 / 4);
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_ANA_SEQ_INCLUDE |
			     WM2000_MODE_POWER_DOWN);
	} else {
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_POWER_DOWN);
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_SYS_STATUS,
			     WM2000_STATUS_POWER_DOWN_COMPLETE)) {
		dev_err(&i2c->dev, "Timeout waiting for ANC power down\n");
		return -ETIMEDOUT;
	}

	if (!wm2000_poll_bit(i2c, WM2000_REG_ANC_STAT,
			     WM2000_ANC_ENG_IDLE)) {
		dev_err(&i2c->dev, "Timeout waiting for ANC engine idle\n");
		return -ETIMEDOUT;
	}

	regulator_bulk_disable(WM2000_NUM_SUPPLIES, wm2000->supplies);

	dev_dbg(&i2c->dev, "powered off\n");
	wm2000->anc_mode = ANC_OFF;

	return 0;
}
