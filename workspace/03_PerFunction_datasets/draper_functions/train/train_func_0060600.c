db_print_columns(char* _b, const int _l, const db_key_t* _c, const int _n)
{
	int i, ret, len = 0;

	if ((!_c) || (!_n) || (!_b) || (!_l)) {
		LM_ERR("Invalid parameter value\n");
		return -1;
	}

	for(i = 0; i < _n; i++)	{
		if (i == (_n - 1)) {
			ret = snprintf(_b + len, _l - len, "%.*s ", _c[i]->len, _c[i]->s);
			if (ret < 0 || ret >= (_l - len)) goto error;
			len += ret;
		} else {
			ret = snprintf(_b + len, _l - len, "%.*s,", _c[i]->len, _c[i]->s);
			if (ret < 0 || ret >= (_l - len)) goto error;
			len += ret;
		}
	}
	return len;

	error:
	LM_ERR("Error in snprintf\n");
	return -1;
}
