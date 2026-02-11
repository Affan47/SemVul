_sum_len_string_dict (const char *key, xmmsv_t *val, void *userdata)
{
	const char *arg;
	int *extra = (int *) userdata;

	if (xmmsv_get_type (val) == XMMSV_TYPE_NONE) {
		*extra += strlen (key) + 1;
	} else if (xmmsv_get_string (val, &arg)) {

		*extra += strlen (key) + strlen (arg) + 2;
	} else {
		x_api_warning ("with non-string argument");
	}
}
