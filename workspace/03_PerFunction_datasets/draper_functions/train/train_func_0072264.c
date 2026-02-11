dib7000p_i2c_enumeration(struct i2c_adapter *i2c, int no_of_demods, u8 default_addr, struct dib7000p_config cfg[])
{
	struct dib7000p_state *dpst;
	int k = 0;
	u8 new_addr = 0;

	dpst = kzalloc(sizeof(struct dib7000p_state), GFP_KERNEL);
	if (!dpst)
		return -ENOMEM;

	dpst->i2c_adap = i2c;
	mutex_init(&dpst->i2c_buffer_lock);

	for (k = no_of_demods - 1; k >= 0; k--) {
		dpst->cfg = cfg[k];


		if (cfg[k].default_i2c_addr != 0)
			new_addr = cfg[k].default_i2c_addr + (k << 1);
		else
			new_addr = (0x40 + k) << 1;
		dpst->i2c_addr = new_addr;
		dib7000p_write_word(dpst, 1287, 0x0003);
		if (dib7000p_identify(dpst) != 0) {
			dpst->i2c_addr = default_addr;
			dib7000p_write_word(dpst, 1287, 0x0003);
			if (dib7000p_identify(dpst) != 0) {
				dprintk("DiB7000P #%d: not identified\n", k);
				kfree(dpst);
				return -EIO;
			}
		}


		dib7000p_set_output_mode(dpst, OUTMODE_DIVERSITY);


		dib7000p_write_word(dpst, 1285, (new_addr << 2) | 0x2);

		dprintk("IC %d initialized (to i2c_address 0x%x)", k, new_addr);
	}

	for (k = 0; k < no_of_demods; k++) {
		dpst->cfg = cfg[k];
		if (cfg[k].default_i2c_addr != 0)
			dpst->i2c_addr = (cfg[k].default_i2c_addr + k) << 1;
		else
			dpst->i2c_addr = (0x40 + k) << 1;


		dib7000p_write_word(dpst, 1285, dpst->i2c_addr << 2);


		dib7000p_set_output_mode(dpst, OUTMODE_HIGH_Z);
	}

	kfree(dpst);
	return 0;
}
