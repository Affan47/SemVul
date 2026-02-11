add_other_freq_entries(struct dvb_file *dvb_file,
				   struct dvb_v5_fe_parms *parms,
				   struct dvb_v5_descriptors *dvb_desc)
{
	int i;
	uint32_t freq, shift = 0;
	enum dvb_sat_polarization pol = POLARIZATION_OFF;

	if (!dvb_desc->nit_table.frequency)
		return;

	pol = dvb_desc->nit_table.pol;

	shift = estimate_freq_shift(parms);

	for (i = 0; i < dvb_desc->nit_table.frequency_len; i++) {
		freq = dvb_desc->nit_table.frequency[i];

		if (new_freq_is_needed(dvb_file->first_entry, NULL, freq, pol,
				       shift))
			add_new_freq(dvb_file->first_entry, freq);
	}
}
