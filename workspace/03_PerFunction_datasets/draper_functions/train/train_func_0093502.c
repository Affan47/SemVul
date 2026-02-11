cx25840_ir_tx_s_parameters(struct v4l2_subdev *sd,
				      struct v4l2_subdev_ir_parameters *p)
{
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	struct i2c_client *c;
	struct v4l2_subdev_ir_parameters *o;
	u16 txclk_divider;

	if (ir_state == NULL)
		return -ENODEV;

	if (p->shutdown)
		return cx25840_ir_tx_shutdown(sd);

	if (p->mode != V4L2_SUBDEV_IR_MODE_PULSE_WIDTH)
		return -ENOSYS;

	c = ir_state->c;
	o = &ir_state->tx_params;
	mutex_lock(&ir_state->tx_params_lock);

	o->shutdown = p->shutdown;

	p->mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;
	o->mode = p->mode;

	p->bytes_per_data_element = sizeof(union cx25840_ir_fifo_rec);
	o->bytes_per_data_element = p->bytes_per_data_element;


	irqenable_tx(sd, 0);
	control_tx_enable(c, false);

	control_tx_modulation_enable(c, p->modulation);
	o->modulation = p->modulation;

	if (p->modulation) {
		p->carrier_freq = txclk_tx_s_carrier(c, p->carrier_freq,
						     &txclk_divider);
		o->carrier_freq = p->carrier_freq;

		p->duty_cycle = cduty_tx_s_duty_cycle(c, p->duty_cycle);
		o->duty_cycle = p->duty_cycle;

		p->max_pulse_width =
			(u32) pulse_width_count_to_ns(FIFO_RXTX, txclk_divider);
	} else {
		p->max_pulse_width =
			    txclk_tx_s_max_pulse_width(c, p->max_pulse_width,
						       &txclk_divider);
	}
	o->max_pulse_width = p->max_pulse_width;
	atomic_set(&ir_state->txclk_divider, txclk_divider);

	p->resolution = clock_divider_to_resolution(txclk_divider);
	o->resolution = p->resolution;


	control_tx_irq_watermark(c, TX_FIFO_HALF_EMPTY);

	control_tx_polarity_invert(c, p->invert_carrier_sense);
	o->invert_carrier_sense = p->invert_carrier_sense;


	o->invert_level = p->invert_level;

	o->interrupt_enable = p->interrupt_enable;
	o->enable = p->enable;
	if (p->enable) {

		if (p->interrupt_enable)
			irqenable_tx(sd, IRQEN_TSE);
		control_tx_enable(c, p->enable);
	}

	mutex_unlock(&ir_state->tx_params_lock);
	return 0;
}
