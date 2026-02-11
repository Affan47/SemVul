expando_create(const char *key, EXPANDO_FUNC func, ...)
{
        EXPANDO_REC *rec;
        const char *signal;
	va_list va;

	g_return_if_fail(key != NULL && *key != '\0');
	g_return_if_fail(func != NULL);

	if (key[1] != '\0')
		rec = g_hash_table_lookup(expandos, key);
	else {

		rec = CHAR_EXPANDO(*key);
	}

	if (rec != NULL)
		rec->signals = 0;
	else {
		rec = g_new0(EXPANDO_REC, 1);
                if (key[1] != '\0')
			g_hash_table_insert(expandos, g_strdup(key), rec);
		else
			char_expandos[(int) (unsigned char) *key] = rec;
	}

	rec->func = func;

	va_start(va, func);
	while ((signal = (const char *) va_arg(va, const char *)) != NULL)
               expando_add_signal(key, signal, (int) va_arg(va, int));
        va_end(va);
}
