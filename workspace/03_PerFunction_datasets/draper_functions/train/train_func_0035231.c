_CONF_add_string(CONF *conf, CONF_VALUE *section, CONF_VALUE *value)
	{
	CONF_VALUE *v = NULL;
	STACK_OF(CONF_VALUE) *ts;

	ts = (STACK_OF(CONF_VALUE) *)section->value;

	value->section=section->section;
	if (!sk_CONF_VALUE_push(ts,value))
		{
		return 0;
		}

	v = lh_CONF_VALUE_insert(conf->data, value);
	if (v != NULL)
		{
		(void)sk_CONF_VALUE_delete_ptr(ts,v);
		OPENSSL_free(v->name);
		OPENSSL_free(v->value);
		OPENSSL_free(v);
		}
	return 1;
	}
