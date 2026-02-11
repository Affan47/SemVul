set_qam_measurement(struct drxk_state *state,
			     enum e_drxk_constellation modulation,
			     u32 symbol_rate)
{
	u32 fec_bits_desired = 0;
	u32 fec_rs_period_total = 0;
	u16 fec_rs_prescale = 0;
	u16 fec_rs_period = 0;
	int status = 0;

	dprintk(1, "\n");

	fec_rs_prescale = 1;


	switch (modulation) {
	case DRX_CONSTELLATION_QAM16:
		fec_bits_desired = 4 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM32:
		fec_bits_desired = 5 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM64:
		fec_bits_desired = 6 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM128:
		fec_bits_desired = 7 * symbol_rate;
		break;
	case DRX_CONSTELLATION_QAM256:
		fec_bits_desired = 8 * symbol_rate;
		break;
	default:
		status = -EINVAL;
	}
	if (status < 0)
		goto error;

	fec_bits_desired /= 1000;
	fec_bits_desired *= 500;


	fec_rs_period_total = (fec_bits_desired / 1632UL) + 1;


	fec_rs_prescale = 1 + (u16) (fec_rs_period_total >> 16);
	if (fec_rs_prescale == 0) {

		status = -EINVAL;
		if (status < 0)
			goto error;
	}
	fec_rs_period =
		((u16) fec_rs_period_total +
		(fec_rs_prescale >> 1)) / fec_rs_prescale;


	status = write16(state, FEC_RS_MEASUREMENT_PERIOD__A, fec_rs_period);
	if (status < 0)
		goto error;
	status = write16(state, FEC_RS_MEASUREMENT_PRESCALE__A,
			 fec_rs_prescale);
	if (status < 0)
		goto error;
	status = write16(state, FEC_OC_SNC_FAIL_PERIOD__A, fec_rs_period);
error:
	if (status < 0)
		pr_err("Error %d on %s\n", status, __func__);
	return status;
}
