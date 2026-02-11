ct_mixer_get_mem(struct ct_mixer **rmixer)
{
	struct ct_mixer *mixer;
	int err;

	*rmixer = NULL;

	mixer = kzalloc(sizeof(*mixer), GFP_KERNEL);
	if (!mixer)
		return -ENOMEM;

	mixer->amixers = kzalloc(sizeof(void *)*(NUM_CT_AMIXERS*CHN_NUM),
				 GFP_KERNEL);
	if (!mixer->amixers) {
		err = -ENOMEM;
		goto error1;
	}
	mixer->sums = kzalloc(sizeof(void *)*(NUM_CT_SUMS*CHN_NUM), GFP_KERNEL);
	if (!mixer->sums) {
		err = -ENOMEM;
		goto error2;
	}

	*rmixer = mixer;
	return 0;

error2:
	kfree(mixer->amixers);
error1:
	kfree(mixer);
	return err;
}
