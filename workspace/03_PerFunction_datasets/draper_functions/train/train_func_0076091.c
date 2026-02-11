gkrellm_effect_string_value(gchar *effect_string)
	{
	if (effect_string)
		return (strcmp(effect_string, "shadow") == 0) ? 1 : 0;
	return 0;
	}
