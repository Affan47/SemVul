calculate_fvifa (gnm_float rate, gnm_float nper)
{

	if (rate == 0)
		return nper;
	else
		return pow1pm1 (rate, nper) / rate;
}
