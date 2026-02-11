tether_set_return(DBusMessageIter *iter, const char *error,
		void *user_data)
{
	struct tether_enable *tether = user_data;
	char *str;

	str = strrchr(tether->path, '/');
	if (str != NULL)
		str++;
	else
		str = tether->path;

	if (error == NULL) {
		fprintf(stdout, "%s tethering for %s\n",
				tether->enable == TRUE ? "Enabled": "Disabled",
				str);
	} else
		fprintf(stderr, "Error %s %s tethering: %s\n",
				tether->enable == TRUE ?
				"enabling": "disabling", str, error);

	g_free(tether->path);
	g_free(user_data);

	return 0;
}
