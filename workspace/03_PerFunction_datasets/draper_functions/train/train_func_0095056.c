mt312_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct mt312_state *state = fe->demodulator_priv;

	u8 val = 0x00;
	int ret;

	switch (state->id) {
	case ID_ZL10313:
		ret = mt312_readreg(state, GPP_CTRL, &val);
		if (ret < 0)
			goto error;


		val &= 0x80;
		break;
	}

	if (enable)
		val |= 0x40;
	else
		val &= ~0x40;

	ret = mt312_writereg(state, GPP_CTRL, val);

error:
	return ret;
}
