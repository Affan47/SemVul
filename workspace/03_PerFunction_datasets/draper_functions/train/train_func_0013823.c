or51132_setmode(struct dvb_frontend* fe)
{
	struct or51132_state* state = fe->demodulator_priv;
	u8 cmd_buf1[3] = {0x04, 0x01, 0x5f};
	u8 cmd_buf2[3] = {0x1c, 0x00, 0 };

	dprintk("setmode %d\n",(int)state->current_modulation);

	switch (state->current_modulation) {
	case VSB_8:

		cmd_buf1[2] = 0x50;

		cmd_buf2[1] = 0x03;

		cmd_buf2[2] = 0x06;
		break;


	case QAM_AUTO:

		cmd_buf2[2] = 0x4f;
		break;
	case QAM_256:

		cmd_buf2[2] = 0x45;
		break;
	case QAM_64:

		cmd_buf2[2] = 0x43;
		break;
	default:
		printk(KERN_WARNING
		       "or51132: setmode: Modulation set to unsupported value (%d)\n",
		       state->current_modulation);
		return -EINVAL;
	}


	if (or51132_writebuf(state, cmd_buf1, 3)) {
		printk(KERN_WARNING "or51132: set_mode error 1\n");
		return -EREMOTEIO;
	}
	dprintk("set #1 to %02x\n", cmd_buf1[2]);


	if (or51132_writebuf(state, cmd_buf2, 3)) {
		printk(KERN_WARNING "or51132: set_mode error 2\n");
		return -EREMOTEIO;
	}
	dprintk("set #6 to 0x%02x%02x\n", cmd_buf2[1], cmd_buf2[2]);

	return 0;
}
