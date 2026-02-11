UI_get0_result_string(UI_STRING *uis)
	{
	if (!uis)
		return NULL;
	switch(uis->type)
		{
	case UIT_PROMPT:
	case UIT_VERIFY:
		return uis->result_buf;
	default:
		return NULL;
		}
	}
