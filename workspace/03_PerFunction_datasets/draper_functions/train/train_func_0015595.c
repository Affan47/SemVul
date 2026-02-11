isCharStyle(void) const
{


	const gchar * szValue = NULL;
	if (getAttribute(PT_TYPE_ATTRIBUTE_NAME, szValue))
		if (szValue && szValue[0])
			return g_ascii_strcasecmp(szValue, "C") == 0;


	return false;
}
