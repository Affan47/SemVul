gpk_get_pretty_arch (const gchar *arch)
{
	const gchar *id = NULL;

	if (arch[0] == '\0')
		goto out;


	if (g_str_has_prefix (arch, "i")) {

		id = _("32-bit");
		goto out;
	}


	if (g_str_has_suffix (arch, "64")) {

		id = _("64-bit");
		goto out;
	}
out:
	return id;
}
