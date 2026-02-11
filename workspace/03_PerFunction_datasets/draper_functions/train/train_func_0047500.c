innodb_rec_per_key(

	dict_index_t*	index,
	ulint		i,

	ha_rows		records)
{
	ha_rows		rec_per_key;

	ut_ad(i < dict_index_get_n_unique(index));


	if (index->stat_n_diff_key_vals[i + 1] == 0) {

		rec_per_key = records;
	} else if (srv_innodb_stats_method == SRV_STATS_NULLS_IGNORED) {
		ib_int64_t	num_null;


		num_null = records - index->stat_n_non_null_key_vals[i];


		num_null = (num_null < 0) ? 0 : num_null;


		if (index->stat_n_diff_key_vals[i + 1] <= num_null) {
			rec_per_key = 1;
		} else {


			rec_per_key = (ha_rows)(
				(records - num_null)
				/ (index->stat_n_diff_key_vals[i + 1]
				   - num_null));
		}
	} else {
		rec_per_key = (ha_rows)
			 (records / index->stat_n_diff_key_vals[i + 1]);
	}

	return(rec_per_key);
}
