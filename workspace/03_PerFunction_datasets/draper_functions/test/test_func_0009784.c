increment_class0()
{
    const uint8_t *data = _str.udata();
    int len = _str.length();
    bool is_list = (data[1] == T_LIST);

    if (_pos != 0)
	_coviter++;
    else
	_pos = FIRST_POS;

    if (_pos == FIRST_POS && _coviter) {
	if (*_coviter < USHORT_AT(data + (is_list ? 2 : RANGES_HEADERSIZE)))
	    return;
	_pos = (is_list ? LIST_HEADERSIZE : RANGES_HEADERSIZE);
    }

    while (_pos > 0 && _pos < len && _coviter) {
	Glyph g = *_coviter;
	if (is_list) {
	    _pos = LIST_HEADERSIZE + LIST_RECSIZE*(g - USHORT_AT(data + 2));
	    if (_pos >= len)
		break;
	    else if (USHORT_AT(data + _pos) == 0)
		return;
	    _coviter++;
	} else {
	    if (g < USHORT_AT(data + _pos))
		return;
	    else if (g > USHORT_AT(data + _pos + 2))
		_pos += RANGES_RECSIZE;
	    else if (USHORT_AT(data + _pos + 4) == 0)
		return;
	    else
		_coviter.forward_to(USHORT_AT(data + _pos + 2) + 1);
	}
    }

    if (_coviter)
	_pos = LAST_POS;
    else
	_pos = len;
}
