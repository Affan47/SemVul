wm2000_exit_standby(struct i2c_client *i2c, int analogue)
{
	struct wm2000_priv *wm2000 = dev_get_drvdata(&i2c->dev);

	if (WARN_ON(wm2000->anc_mode != ANC_STANDBY))
		return -EINVAL;

	wm2000_write(i2c, WM2000_REG_SYS_CTL1, 0);

	if (analogue) {
		wm2000_write(i2c, WM2000_REG_ANA_VMID_PU_TIME, 248 / 4);

		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_ANA_SEQ_INCLUDE |
			     WM2000_MODE_THERMAL_ENABLE |
			     WM2000_MODE_MOUSE_ENABLE);
	} else {
		wm2000_write(i2c, WM2000_REG_SYS_MODE_CNTRL,
			     WM2000_MODE_THERMAL_ENABLE |
			     WM2000_MODE_MOUSE_ENABLE);
	}

	wm2000_write(i2c, WM2000_REG_SYS_CTL2, WM2000_RAM_SET);
	wm2000_write(i2c, WM2000_REG_SYS_CTL2, WM2000_ANC_INT_N_CLR);

	if (!wm2000_poll_bit(i2c, WM2000_REG_SYS_STATUS,
			     WM2000_STATUS_MOUSE_ACTIVE)) {
		dev_err(&i2c->dev, "Timed out waiting for MOUSE\n");
		return -ETIMEDOUT;
	}

	wm2000->anc_mode = ANC_ACTIVE;
	dev_dbg(&i2c->dev, "MOUSE active\n");
	if (analogue)
		dev_dbg(&i2c->dev, "Analogue enabled\n");

	return 0;
}
