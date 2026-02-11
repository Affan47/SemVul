rotary_encoder_half_period_irq(int irq, void *dev_id)
{
	struct rotary_encoder *encoder = dev_id;
	int state;

	state = rotary_encoder_get_state(encoder->pdata);

	switch (state) {
	case 0x00:
	case 0x03:
		if (state != encoder->last_stable) {
			rotary_encoder_report_event(encoder);
			encoder->last_stable = state;
		}
		break;

	case 0x01:
	case 0x02:
		encoder->dir = (encoder->last_stable + state) & 0x01;
		break;
	}

	return IRQ_HANDLED;
}
