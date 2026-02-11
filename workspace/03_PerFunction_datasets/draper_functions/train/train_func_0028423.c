soc_tplg_create_tlv_db_scale(struct soc_tplg *tplg,
	struct snd_kcontrol_new *kc, struct snd_soc_tplg_tlv_dbscale *scale)
{
	unsigned int item_len = 2 * sizeof(unsigned int);
	unsigned int *p;

	p = kzalloc(item_len + 2 * sizeof(unsigned int), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	p[0] = SNDRV_CTL_TLVT_DB_SCALE;
	p[1] = item_len;
	p[2] = scale->min;
	p[3] = (scale->step & TLV_DB_SCALE_MASK)
			| (scale->mute ? TLV_DB_SCALE_MUTE : 0);

	kc->tlv.p = (void *)p;
	return 0;
}
