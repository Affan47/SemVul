lgdt3305_passband_digital_agc(struct lgdt3305_state *state,
					 struct dtv_frontend_properties *p)
{
	u16 agc_ref;

	switch (p->modulation) {
	case VSB_8:
		agc_ref = 0x32c4;
		break;
	case QAM_64:
		agc_ref = 0x2a00;
		break;
	case QAM_256:
		agc_ref = 0x2a80;
		break;
	default:
		return -EINVAL;
	}

	lg_dbg("agc ref: 0x%04x\n", agc_ref);

	lgdt3305_write_reg(state, LGDT3305_DGTL_AGC_REF_1, agc_ref >> 8);
	lgdt3305_write_reg(state, LGDT3305_DGTL_AGC_REF_2, agc_ref & 0xff);

	return 0;
}
