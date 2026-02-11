lgdt3306a_spectral_inversion(struct lgdt3306a_state *state,
				       struct dtv_frontend_properties *p,
				       int inversion)
{
	int ret = 0;

	dbg_info("(%d)\n", inversion);
#if 0


	ret = lgdt3306a_set_inversion(state, inversion);

	switch (p->modulation) {
	case VSB_8:

		ret = lgdt3306a_set_inversion_auto(state, 0);
		break;
	case QAM_64:
	case QAM_256:

		ret = lgdt3306a_set_inversion_auto(state, 1);
		break;
	default:
		ret = -EINVAL;
	}
#endif
	return ret;
}
