lx_restore_display_ctlr(struct lxfb_par *par)
{
	uint32_t filt;
	int i;

	wrmsrl(MSR_LX_SPARE_MSR, par->msr.dcspare);

	for (i = 0; i < ARRAY_SIZE(par->dc); i++) {
		switch (i) {
		case DC_UNLOCK:

			write_dc(par, DC_UNLOCK, DC_UNLOCK_UNLOCK);
			break;

		case DC_GENERAL_CFG:
		case DC_DISPLAY_CFG:

			write_dc(par, i, 0);
			break;

		case DC_DV_CTL:

			write_dc(par, i, par->dc[i] | DC_DV_CTL_CLEAR_DV_RAM);

		case DC_RSVD_1:
		case DC_RSVD_2:
		case DC_RSVD_3:
		case DC_LINE_CNT:
		case DC_PAL_ADDRESS:
		case DC_PAL_DATA:
		case DC_DFIFO_DIAG:
		case DC_CFIFO_DIAG:
		case DC_FILT_COEFF1:
		case DC_FILT_COEFF2:
		case DC_RSVD_4:
		case DC_RSVD_5:

			break;

		default:
			write_dc(par, i, par->dc[i]);
		}
	}


	write_dc(par, DC_PAL_ADDRESS, 0);
	for (i = 0; i < ARRAY_SIZE(par->dc_pal); i++)
		write_dc(par, DC_PAL_DATA, par->dc_pal[i]);


	filt = par->dc[DC_IRQ_FILT_CTL] | DC_IRQ_FILT_CTL_H_FILT_SEL;
	for (i = 0; i < ARRAY_SIZE(par->hcoeff); i += 2) {
		write_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		write_dc(par, DC_FILT_COEFF1, par->hcoeff[i]);
		write_dc(par, DC_FILT_COEFF2, par->hcoeff[i + 1]);
	}


	filt &= ~DC_IRQ_FILT_CTL_H_FILT_SEL;
	for (i = 0; i < ARRAY_SIZE(par->vcoeff); i++) {
		write_dc(par, DC_IRQ_FILT_CTL, (filt & 0xffffff00) | i);
		write_dc(par, DC_FILT_COEFF1, par->vcoeff[i]);
	}
}
