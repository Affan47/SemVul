__db_txnlist_gen(env, hp, incr, min, max)
	ENV *env;
	DB_TXNHEAD *hp;
	int incr;
	u_int32_t min, max;
{
	int ret;


	if (incr < 0) {
		--hp->generation;
		memmove(hp->gen_array, &hp->gen_array[1],
		    (hp->generation + 1) * sizeof(hp->gen_array[0]));
	} else {
		++hp->generation;
		if (hp->generation >= hp->gen_alloc) {
			hp->gen_alloc *= 2;
			if ((ret = __os_realloc(env, hp->gen_alloc *
			    sizeof(hp->gen_array[0]), &hp->gen_array)) != 0)
				return (ret);
		}
		memmove(&hp->gen_array[1], &hp->gen_array[0],
		    hp->generation * sizeof(hp->gen_array[0]));
		hp->gen_array[0].generation = hp->generation;
		hp->gen_array[0].txn_min = min;
		hp->gen_array[0].txn_max = max;
	}
	return (0);
}
