drbg_hash_update(struct drbg_state *drbg, struct list_head *seed,
			    int reseed)
{
	int ret = 0;
	struct drbg_string data1, data2;
	LIST_HEAD(datalist);
	LIST_HEAD(datalist2);
	unsigned char *V = drbg->scratchpad;
	unsigned char prefix = DRBG_PREFIX1;

	if (!seed)
		return -EINVAL;

	if (reseed) {

		memcpy(V, drbg->V, drbg_statelen(drbg));
		drbg_string_fill(&data1, &prefix, 1);
		list_add_tail(&data1.list, &datalist);
		drbg_string_fill(&data2, V, drbg_statelen(drbg));
		list_add_tail(&data2.list, &datalist);
	}
	list_splice_tail(seed, &datalist);


	ret = drbg_hash_df(drbg, drbg->V, drbg_statelen(drbg), &datalist);
	if (ret)
		goto out;


	prefix = DRBG_PREFIX0;
	drbg_string_fill(&data1, &prefix, 1);
	list_add_tail(&data1.list, &datalist2);
	drbg_string_fill(&data2, drbg->V, drbg_statelen(drbg));
	list_add_tail(&data2.list, &datalist2);

	ret = drbg_hash_df(drbg, drbg->C, drbg_statelen(drbg), &datalist2);

out:
	memset(drbg->scratchpad, 0, drbg_statelen(drbg));
	return ret;
}
