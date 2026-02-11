proxy_dump_data_005(gpointer key, gpointer value, gpointer context)
{
	if (*(char *)value != '\0')
		g_string_append_printf(context, "%s=%s ", (char *)key, (char *)value);
	else
		g_string_append_printf(context, "%s ", (char *)key);
}
