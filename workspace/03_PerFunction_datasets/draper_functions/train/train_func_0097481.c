stv090x_set_mis(struct stv090x_state *state, int mis)
{
	u32 reg;

	if (mis < 0 || mis > 255) {
		dprintk(FE_DEBUG, 1, "Disable MIS filtering");
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x00);
		if (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			goto err;
	} else {
		dprintk(FE_DEBUG, 1, "Enable MIS filtering - %d", mis);
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x01);
		if (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, ISIENTRY, mis) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, ISIBITENA, 0xff) < 0)
			goto err;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}
