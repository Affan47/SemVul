free_string(UI_STRING *uis)
	{
	if (uis->flags & OUT_STRING_FREEABLE)
		{
		OPENSSL_free((char *)uis->out_string);
		switch(uis->type)
			{
		case UIT_BOOLEAN:
			OPENSSL_free((char *)uis->_.boolean_data.action_desc);
			OPENSSL_free((char *)uis->_.boolean_data.ok_chars);
			OPENSSL_free((char *)uis->_.boolean_data.cancel_chars);
			break;
		default:
			break;
			}
		}
	OPENSSL_free(uis);
	}
