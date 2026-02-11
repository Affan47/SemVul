sv_from_value_string (xmmsv_t *val)
{
	int ret;
	const char *str = NULL;

	ret = xmmsv_get_string (val, &str);

	if (ret == 0) {
		croak("could not fetch string value");
	}

	return newSVpv (str, 0);
}
