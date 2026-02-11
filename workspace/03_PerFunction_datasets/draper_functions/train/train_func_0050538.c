local__parse_msf_(const char *s, unsigned sample_rate)
{
	FLAC__int64 ret, field;
	char c;

	c = *s++;
	if(c >= '0' && c <= '9')
		field = (c - '0');
	else
		return -1;
	while(':' != (c = *s++)) {
		if(c >= '0' && c <= '9')
			field = field * 10 + (c - '0');
		else
			return -1;
	}

	ret = field * 60 * sample_rate;

	c = *s++;
	if(c >= '0' && c <= '9')
		field = (c - '0');
	else
		return -1;
	if(':' != (c = *s++)) {
		if(c >= '0' && c <= '9') {
			field = field * 10 + (c - '0');
			c = *s++;
			if(c != ':')
				return -1;
		}
		else
			return -1;
	}

	if(field >= 60)
		return -1;

	ret += field * sample_rate;

	c = *s++;
	if(c >= '0' && c <= '9')
		field = (c - '0');
	else
		return -1;
	if('\0' != (c = *s++)) {
		if(c >= '0' && c <= '9') {
			field = field * 10 + (c - '0');
			c = *s++;
		}
		else
			return -1;
	}

	if(c != '\0')
		return -1;

	if(field >= 75)
		return -1;

	ret += field * (sample_rate / 75);

	return ret;
}
