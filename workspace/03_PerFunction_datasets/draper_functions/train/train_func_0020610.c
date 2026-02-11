eap_method_default_file_chooser_filter_new (gboolean privkey)
{
	GtkFileFilter *filter;

	filter = gtk_file_filter_new ();
	if (privkey) {
		gtk_file_filter_add_custom (filter, GTK_FILE_FILTER_FILENAME, default_filter_privkey, NULL, NULL);
		gtk_file_filter_set_name (filter, _("DER, PEM, or PKCS#12 private keys (*.der, *.pem, *.p12, *.key)"));
	} else {
		gtk_file_filter_add_custom (filter, GTK_FILE_FILTER_FILENAME, default_filter_cert, NULL, NULL);
		gtk_file_filter_set_name (filter, _("DER or PEM certificates (*.der, *.pem, *.crt, *.cer)"));
	}
	return filter;
}
