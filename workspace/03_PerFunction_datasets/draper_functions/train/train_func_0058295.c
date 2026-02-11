simple_tuner_attach(struct dvb_frontend *fe,
					 struct i2c_adapter *i2c_adap,
					 u8 i2c_addr,
					 unsigned int type)
{
	struct tuner_simple_priv *priv = NULL;
	int instance;

	if (type >= tuner_count) {
		printk(KERN_WARNING "%s: invalid tuner type: %d (max: %d)\n",
		       __func__, type, tuner_count-1);
		return NULL;
	}


	if (i2c_adap != NULL) {
		u8 b[1];
		struct i2c_msg msg = {
			.addr = i2c_addr, .flags = I2C_M_RD,
			.buf = b, .len = 1,
		};

		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);

		if (1 != i2c_transfer(i2c_adap, &msg, 1))
			printk(KERN_WARNING "tuner-simple %d-%04x: "
			       "unable to probe %s, proceeding anyway.",
			       i2c_adapter_id(i2c_adap), i2c_addr,
			       tuners[type].name);

		if (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	}

	mutex_lock(&tuner_simple_list_mutex);

	instance = hybrid_tuner_request_state(struct tuner_simple_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c_adap, i2c_addr,
					      "tuner-simple");
	switch (instance) {
	case 0:
		mutex_unlock(&tuner_simple_list_mutex);
		return NULL;
	case 1:
		fe->tuner_priv = priv;

		priv->type = type;
		priv->tun  = &tuners[type];
		priv->nr   = simple_devcount++;
		break;
	default:
		fe->tuner_priv = priv;
		break;
	}

	mutex_unlock(&tuner_simple_list_mutex);

	memcpy(&fe->ops.tuner_ops, &simple_tuner_ops,
	       sizeof(struct dvb_tuner_ops));

	if (type != priv->type)
		tuner_warn("couldn't set type to %d. Using %d (%s) instead\n",
			    type, priv->type, priv->tun->name);
	else
		tuner_info("type set to %d (%s)\n",
			   priv->type, priv->tun->name);

	if ((debug) || ((atv_input[priv->nr] > 0) ||
			(dtv_input[priv->nr] > 0))) {
		if (0 == atv_input[priv->nr])
			tuner_info("tuner %d atv rf input will be "
				   "autoselected\n", priv->nr);
		else
			tuner_info("tuner %d atv rf input will be "
				   "set to input %d (insmod option)\n",
				   priv->nr, atv_input[priv->nr]);
		if (0 == dtv_input[priv->nr])
			tuner_info("tuner %d dtv rf input will be "
				   "autoselected\n", priv->nr);
		else
			tuner_info("tuner %d dtv rf input will be "
				   "set to input %d (insmod option)\n",
				   priv->nr, dtv_input[priv->nr]);
	}

	strlcpy(fe->ops.tuner_ops.info.name, priv->tun->name,
		sizeof(fe->ops.tuner_ops.info.name));

	return fe;
}
