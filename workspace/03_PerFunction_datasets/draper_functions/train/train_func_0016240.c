size() const throw ()
{
    if (_str.length() == 0)
	return -1;
    const uint8_t *data = _str.udata();
    if (data[1] == T_LIST)
	return (_str.length() - HEADERSIZE) / LIST_RECSIZE;
    else if (data[1] == T_RANGES) {
	data += _str.length() - RANGES_RECSIZE;
	return USHORT_AT(data + 4) + USHORT_AT(data + 2) - USHORT_AT(data) + 1;
    } else if (data[1] == T_X_BYTEMAP)
	return ULONG_AT(data + 4);
    else
	return -1;
}
