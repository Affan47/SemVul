amixer_rsc_init(struct amixer *amixer,
			   const struct amixer_desc *desc,
			   struct amixer_mgr *mgr)
{
	int err;

	err = rsc_init(&amixer->rsc, amixer->idx[0],
			AMIXER, desc->msr, mgr->mgr.hw);
	if (err)
		return err;


	amixer->rsc.ops = &amixer_basic_rsc_ops;
	amixer->ops = &amixer_ops;
	amixer->input = NULL;
	amixer->sum = NULL;

	amixer_setup(amixer, NULL, 0, NULL);

	return 0;
}
