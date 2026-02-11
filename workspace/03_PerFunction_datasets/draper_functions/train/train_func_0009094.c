sv_from_value_int (xmmsv_t *val)
{
	int ret, num;

	ret = xmmsv_get_int (val, &num);

	if (ret == 0) {
		croak("could not fetch int value");
	}

	return newSViv (num);
}
