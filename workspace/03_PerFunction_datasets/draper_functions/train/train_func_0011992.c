count_invalid_entries(const h10db_dat_t* h10db_dat, int num_dat_entries)
{
	int i;
	uint32_t ret = 0;
	for (i = 0;i < num_dat_entries;i++) {
		if (h10db_dat[i].status == 1) {
			ret++;
		}
	}
	return ret;
}
