lookup_dynamic_library()
{
	GModule *mod = g_module_open(NOTIFY_FILE, G_MODULE_BIND_LAZY);
#ifndef G_OS_WIN32

	if(!mod)
	{
		gchar notify_file_str[] = NOTIFY_FILE;
		const size_t version_index = G_N_ELEMENTS(NOTIFY_FILE) - 2;
		for(gchar i = '3'; ((!mod) && (i > '0')); --i)
		{
			notify_file_str[version_index] = i;
			mod = g_module_open(notify_file_str, G_MODULE_BIND_LAZY);
		}
	}
#endif
	return mod;
}
