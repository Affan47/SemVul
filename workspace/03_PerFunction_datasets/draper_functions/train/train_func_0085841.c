operator++(int)
{
    const uint8_t *data = _str.udata();
    int len = _str.length();
    if (_pos >= len
	|| (data[1] == T_RANGES && ++_value <= USHORT_AT(data + _pos + 2)))
	return;
    switch (data[1]) {
    case T_LIST:
	_pos += LIST_RECSIZE;
    normal_pos_setting:
	_value = _pos >= len ? 0 : USHORT_AT(data + _pos);
	break;
    case T_RANGES:
	_pos += RANGES_RECSIZE;
	goto normal_pos_setting;
    case T_X_BYTEMAP:
	for (++_pos; _pos < len && !data[_pos]; ++_pos)
	    ;
	_value = _pos >= len ? 0 : _pos - 8;
	break;
    }
}
