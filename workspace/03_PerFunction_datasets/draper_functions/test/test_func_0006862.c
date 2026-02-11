set_floor_freq_default(struct rapl_domain *rd, bool mode)
{
	int nr_powerlimit = find_nr_power_limit(rd);


	rapl_write_data_raw(rd, PL1_CLAMP, mode);


	if (nr_powerlimit > 1) {
		rapl_write_data_raw(rd, PL2_ENABLE, mode);
		rapl_write_data_raw(rd, PL2_CLAMP, mode);
	}
}
