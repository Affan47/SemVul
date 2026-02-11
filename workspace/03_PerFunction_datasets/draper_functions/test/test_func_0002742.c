get_certificate_path(const gchar *host, const gchar *port, const gchar *fp)
{
	if (fp != NULL && prefs_common_unsafe_ssl_certs())
		return g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
			  "certs", G_DIR_SEPARATOR_S,
			  host, ".", port, ".", fp, ".cert", NULL);
	else
		return g_strconcat(get_rc_dir(), G_DIR_SEPARATOR_S,
			  "certs", G_DIR_SEPARATOR_S,
			  host, ".", port, ".cert", NULL);
}
