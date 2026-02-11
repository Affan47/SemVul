xmmsv_new_dict (void)
{
	xmmsv_t *val = xmmsv_new (XMMSV_TYPE_DICT);

	if (val) {
		val->value.dict = xmmsv_dict_new ();
	}

	return val;
}
