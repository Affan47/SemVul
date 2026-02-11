mt_state_new(random_fn_t rf)
{
	mt_state_t *mts;

	WALLOC0(mts);
	mts->magic = MT_STATE_MAGIC;

	if (rf != NULL)
		mts_seed_with(rf, mts);

	return mts;
}
