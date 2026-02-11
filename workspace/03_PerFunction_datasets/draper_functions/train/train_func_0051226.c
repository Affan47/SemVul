lgdt3306a_set_if(struct lgdt3306a_state *state,
			   struct dtv_frontend_properties *p)
{
	int ret;
	u16 if_freq_khz;
	u8 nco1, nco2;

	switch (p->modulation) {
	case VSB_8:
		if_freq_khz = state->cfg->vsb_if_khz;
		break;
	case QAM_64:
	case QAM_256:
		if_freq_khz = state->cfg->qam_if_khz;
		break;
	default:
		return -EINVAL;
	}

	switch (if_freq_khz) {
	default:
		pr_warn("IF=%d KHz is not supportted, 3250 assumed\n",
			if_freq_khz);

	case 3250:
		nco1 = 0x34;
		nco2 = 0x00;
		break;
	case 3500:
		nco1 = 0x38;
		nco2 = 0x00;
		break;
	case 4000:
		nco1 = 0x40;
		nco2 = 0x00;
		break;
	case 5000:
		nco1 = 0x50;
		nco2 = 0x00;
		break;
	case 5380:
		nco1 = 0x56;
		nco2 = 0x14;
		break;
	}
	ret = lgdt3306a_write_reg(state, 0x0010, nco1);
	if (ret)
		return ret;
	ret = lgdt3306a_write_reg(state, 0x0011, nco2);
	if (ret)
		return ret;

	dbg_info("if_freq=%d KHz->[%04x]\n", if_freq_khz, nco1<<8 | nco2);

	return 0;
}
