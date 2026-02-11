check_sbar_destroy(char *key, char *value, char *script)
{
	if (strncmp(value, script, strlen(script)) == 0 &&
	    value[strlen(script)] == ':') {
                statusbar_item_unregister(key);
		g_free(key);
                g_free(value);
		return TRUE;
	}

        return FALSE;
}
