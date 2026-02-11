CDB___db_tablesize(n_buckets)
	u_int32_t n_buckets;
{
	int i;


	if (n_buckets < 64)
		n_buckets = 64;

	for (i = 0;; ++i) {
		if (list[i].power == 0) {
			--i;
			break;
		}
		if (list[i].power >= n_buckets)
			break;
	}
	return (list[i].prime);
}
