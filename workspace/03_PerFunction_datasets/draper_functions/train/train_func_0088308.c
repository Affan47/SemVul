parse_unitstring(char *str, isc_resourcevalue_t *valuep) {
	char *endp;
	unsigned int len;
	isc_uint64_t value;
	isc_uint64_t unit;

	value = isc_string_touint64(str, &endp, 10);
	if (*endp == 0) {
		*valuep = value;
		return (ISC_R_SUCCESS);
	}

	len = strlen(str);
	if (len < 2 || endp[1] != '\0')
		return (ISC_R_FAILURE);

	switch (str[len - 1]) {
	case 'k':
	case 'K':
		unit = 1024;
		break;
	case 'm':
	case 'M':
		unit = 1024 * 1024;
		break;
	case 'g':
	case 'G':
		unit = 1024 * 1024 * 1024;
		break;
	default:
		return (ISC_R_FAILURE);
	}
	if (value > ISC_UINT64_MAX / unit)
		return (ISC_R_FAILURE);
	*valuep = value * unit;
	return (ISC_R_SUCCESS);
}
