find_attribute(const QByteArray &buf, quint16 type, int *len, int *next = 0)
{
	int at = ATTRIBUTE_AREA_START;
	quint16 _type;
	int _len;
	int _next;

	while(1)
	{
		_next = get_attribute_props(buf, at, &_type, &_len);
		if(_next == -1)
			break;
		if(_type == type)
		{
			*len = _len;
			if(next)
				*next = _next;
			return at;
		}
		at = _next;
	}

	return -1;
}
