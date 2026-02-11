_wind_stringprep_prohibited(const uint32_t *in, size_t in_len,
			    wind_profile_flags flags)
{
    unsigned i;

    for (i = 0; i < in_len; ++i)
	if (_wind_stringprep_error(in[i], flags))
	    return 1;
    return 0;
}
