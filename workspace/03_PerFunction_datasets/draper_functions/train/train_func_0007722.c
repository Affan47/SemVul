cx88_setup_xc3028(struct cx88_core *core, struct xc2028_ctrl *ctl)
{
	memset(ctl, 0, sizeof(*ctl));

	ctl->fname   = XC2028_DEFAULT_FIRMWARE;
	ctl->max_len = 64;

	switch (core->boardnr) {
	case CX88_BOARD_POWERCOLOR_REAL_ANGEL:

		if (core->i2c_algo.udelay < 16)
			core->i2c_algo.udelay = 16;
		break;
	case CX88_BOARD_DVICO_FUSIONHDTV_DVB_T_PRO:
	case CX88_BOARD_WINFAST_DTV1800H:
		ctl->demod = XC3028_FE_ZARLINK456;
		break;
	case CX88_BOARD_KWORLD_ATSC_120:
	case CX88_BOARD_DVICO_FUSIONHDTV_5_PCI_NANO:
		ctl->demod = XC3028_FE_OREN538;
		break;
	case CX88_BOARD_GENIATECH_X8000_MT:


		ctl->disable_power_mgmt = 1;
		break;
	case CX88_BOARD_WINFAST_TV2000_XP_GLOBAL:
	case CX88_BOARD_PROLINK_PV_GLOBAL_XTREME:
	case CX88_BOARD_PROLINK_PV_8000GT:


		break;
	case CX88_BOARD_PINNACLE_HYBRID_PCTV:
	case CX88_BOARD_TERRATEC_CINERGY_HT_PCI_MKII:
		ctl->demod = XC3028_FE_ZARLINK456;
		ctl->mts = 1;
		break;
	default:
		ctl->demod = XC3028_FE_OREN538;
		ctl->mts = 1;
	}
}
