liblo10k1_patch_set_sta_count(liblo10k1_dsp_patch_t *p, int count)
{
	liblo10k1_dsp_cs_t *tmp = NULL;

	if (count > 0) {
		tmp = (liblo10k1_dsp_cs_t *)malloc(sizeof(liblo10k1_dsp_cs_t) * count);
		if (!tmp)
			return LD10K1_ERR_NO_MEM;
		memset(tmp, 0, sizeof(liblo10k1_dsp_cs_t) * count);
	}

	p->sta_count = count;
	if (p->stas)
		free(p->stas);
	p->stas = tmp;
	return 0;
}
