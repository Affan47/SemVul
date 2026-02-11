demod_attach_drxk(struct ngene_channel *chan,
			     struct i2c_adapter *i2c)
{
	struct drxk_config config;

	memset(&config, 0, sizeof(config));
	config.microcode_name = "drxk_a3.mc";
	config.qam_demod_parameter_count = 4;
	config.adr = 0x29 + (chan->number ^ 2);

	chan->fe = dvb_attach(drxk_attach, &config, i2c);
	if (!chan->fe) {
		printk(KERN_ERR "No DRXK found!\n");
		return -ENODEV;
	}
	chan->fe->sec_priv = chan;
	chan->gate_ctrl = chan->fe->ops.i2c_gate_ctrl;
	chan->fe->ops.i2c_gate_ctrl = drxk_gate_ctrl;
	return 0;
}
