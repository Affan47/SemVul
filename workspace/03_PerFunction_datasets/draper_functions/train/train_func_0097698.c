mono_disasm_code (MonoDisHelper *dh, MonoMethod *method, const guchar *ip, const guchar* end)
{
	char *result;
	GString *res = g_string_new ("");

	if (!dh)
		dh = &default_dh;
	while (ip < end) {
		ip = dis_one (res, dh, method, ip, end);
	}

	result = res->str;
	g_string_free (res, FALSE);
	return result;
}
