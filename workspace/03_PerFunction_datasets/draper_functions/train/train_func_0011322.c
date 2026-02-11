operator[](int cindex) const throw ()
{
    if (_str.length() == 0 || cindex < 0)
	return 0;

    const uint8_t *data = _str.udata();
    int count = USHORT_AT(data + 2);
    if (data[1] == T_LIST)
	return (cindex < count ? USHORT_AT(data + cindex * LIST_RECSIZE) : 0);
    else if (data[1] == T_RANGES) {
	int l = 0, r = count;
	data += HEADERSIZE;
	while (l < r) {
	    int m = l + (r - l) / 2;
	    const uint8_t *rec = data + m * RANGES_RECSIZE;
	    int start_cindex = USHORT_AT(rec + 4);
	    if (cindex < start_cindex)
		r = m;
	    else if (cindex < start_cindex + USHORT_AT(rec + 2) - USHORT_AT(rec))
		return USHORT_AT(rec) + cindex - start_cindex;
	    else
		l = m + 1;
	}
	return 0;
    } else
	return 0;
}
