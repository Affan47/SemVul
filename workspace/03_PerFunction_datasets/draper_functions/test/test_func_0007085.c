gsubr(int i)
{
    i += subr_bias(2, ngsubrs());
    if (i < 0 || i >= ngsubrs())
	return 0;
    if (!_gsubrs_cs[i]) {
	const uint8_t *s1 = _gsubrs_index[i];
	int slen = _gsubrs_index[i + 1] - s1;
	String cs = data_string().substring(s1 - data(), slen);
	if (slen == 0)
	    return 0;
	else
	    _gsubrs_cs[i] = new Type2Charstring(cs);
    }
    return _gsubrs_cs[i];
}
