liblo10k1_patch_ctl_set_trans(liblo10k1_dsp_patch_t *p, int idx, int trans)
{
	int i;
	switch (trans) {
		case EMU10K1_GPR_TRANSLATION_NONE:
			break;
		case EMU10K1_GPR_TRANSLATION_TABLE100:
			if (p->ctl[idx].min != 0 && p->ctl[idx].max != 100)
				return LD10K1_EF_ERR_TRANSFORM_TRANS;
			break;
		case EMU10K1_GPR_TRANSLATION_BASS:
		case EMU10K1_GPR_TRANSLATION_TREBLE:
			if (p->ctl[idx].min != 0 && p->ctl[idx].max != 0xFFFFFFFF)
				return LD10K1_EF_ERR_TRANSFORM_TRANS;
			if (p->ctl[idx].count != 5)
				return LD10K1_EF_ERR_TRANSFORM_TRANS;
			break;
		case EMU10K1_GPR_TRANSLATION_ONOFF:
			if (p->ctl[idx].min != 0 && p->ctl[idx].max != 1)
				return LD10K1_EF_ERR_TRANSFORM_TRANS;
			break;
	}
	for (i = 0; i < p->ctl[idx].count; i++)
		if (p->ctl[idx].value[i] < p->ctl[idx].min || p->ctl[idx].value[i] > p->ctl[idx].max)
			return LD10K1_EF_ERR_TRANSFORM_TRANS;
	p->ctl[idx].translation = trans;
	return 0;
}
