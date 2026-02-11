rotary_encoder_quarter_period_irq(int irq, void *dev_id)
{
	struct rotary_encoder *encoder = dev_id;
	unsigned char sum;
	int state;

	state = rotary_encoder_get_state(encoder->pdata);


	sum = (encoder->last_stable << 4) + state;
	switch (sum) {
	case 0x31:
	case 0x10:
	case 0x02:
	case 0x23:
		encoder->dir = 0;
		break;

	case 0x13:
	case 0x01:
	case 0x20:
	case 0x32:
		encoder->dir = 1;
		break;

	default:


		goto out;
	}

	rotary_encoder_report_event(encoder);

out:
	encoder->last_stable = state;
	return IRQ_HANDLED;
}
