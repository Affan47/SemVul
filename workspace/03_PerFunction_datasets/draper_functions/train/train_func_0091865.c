cdf_unpack_summary_info(const cdf_stream_t *sst, cdf_summary_info_header_t *ssi,
    cdf_property_info_t **info, size_t *count)
{
	size_t i, maxcount;
	const cdf_summary_info_header_t *si = sst->sst_tab;
	const cdf_section_declaration_t *sd = (const void *)
	    ((const char *)sst->sst_tab + CDF_SECTION_DECLARATION_OFFSET);

	if (cdf_check_stream_offset(sst, si, sizeof(*si)) == -1 ||
	    cdf_check_stream_offset(sst, sd, sizeof(*sd)) == -1)
		return -1;
	ssi->si_byte_order = CDF_TOLE2(si->si_byte_order);
	ssi->si_os_version = CDF_TOLE2(si->si_os_version);
	ssi->si_os = CDF_TOLE2(si->si_os);
	ssi->si_class = si->si_class;
	cdf_swap_class(&ssi->si_class);
	ssi->si_count = CDF_TOLE2(si->si_count);
	*count = 0;
	maxcount = 0;
	*info = NULL;
	for (i = 0; i < CDF_TOLE4(si->si_count); i++) {
		if (i >= CDF_LOOP_LIMIT) {
			DPRINTF(("Unpack summary info loop limit"));
			errno = EFTYPE;
			return -1;
		}
		if (cdf_read_property_info(sst, CDF_TOLE4(sd->sd_offset),
		    info, count, &maxcount) == -1)
			return -1;
	}
	return 0;
}
