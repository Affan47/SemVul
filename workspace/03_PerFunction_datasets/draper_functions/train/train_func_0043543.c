get_current_state (const gchar *name)
{
	static struct {
		const gchar *name;
		xmms_configparser_state_t state;
	} *ptr, lookup[] = {
		{"xmms", XMMS_CONFIG_STATE_START},
		{"section", XMMS_CONFIG_STATE_SECTION},
		{"property", XMMS_CONFIG_STATE_PROPERTY},
		{NULL, XMMS_CONFIG_STATE_INVALID}
	};

	for (ptr = lookup; ptr && ptr->name; ptr++) {
		if (!strcmp (ptr->name, name)) {
			return ptr->state;
		}
	}

	return XMMS_CONFIG_STATE_INVALID;
}
