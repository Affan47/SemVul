pk_transaction_sqlite_proxy_cb (void *data, gint argc, gchar **argv, gchar **col_name)
{
	PkTransactionDbProxyItem *item = (PkTransactionDbProxyItem *) data;
	gint i;

	g_return_val_if_fail (item != NULL, 0);

	for (i=0; i<argc; i++) {
		if (g_strcmp0 (col_name[i], "proxy_http") == 0) {
			item->proxy_http = g_strdup (argv[i]);
			item->set = TRUE;
		} else if (g_strcmp0 (col_name[i], "proxy_https") == 0) {
			item->proxy_https = g_strdup (argv[i]);
			item->set = TRUE;
		} else if (g_strcmp0 (col_name[i], "proxy_ftp") == 0) {
			item->proxy_ftp = g_strdup (argv[i]);
			item->set = TRUE;
		} else if (g_strcmp0 (col_name[i], "proxy_socks") == 0) {
			item->proxy_socks = g_strdup (argv[i]);
			item->set = TRUE;
		} else if (g_strcmp0 (col_name[i], "no_proxy") == 0) {
			item->no_proxy = g_strdup (argv[i]);
			item->set = TRUE;
		} else if (g_strcmp0 (col_name[i], "pac") == 0) {
			item->pac = g_strdup (argv[i]);
			item->set = TRUE;
		} else {
			g_warning ("%s = %s\n", col_name[i], argv[i]);
		}
	}
	return 0;
}
