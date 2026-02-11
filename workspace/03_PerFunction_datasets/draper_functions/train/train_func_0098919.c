gigolo_describe_scheme(const gchar *scheme)
{
	if (gigolo_str_equal(scheme, "file"))
		return _("Unix Device");
	else if (gigolo_str_equal(scheme, "smb"))
		return _("Windows Share");
	else if (gigolo_str_equal(scheme, "ftp"))
		return _("FTP");
	else if (gigolo_str_equal(scheme, "http"))
		return _("HTTP");
	else if (gigolo_str_equal(scheme, "sftp"))
		return _("SSH");
	else if (gigolo_str_equal(scheme, "obex"))
		return _("Obex");
	else if (gigolo_str_equal(scheme, "dav"))
		return _("WebDAV");
	else if (gigolo_str_equal(scheme, "davs"))
		return _("WebDAV (secure)");
	else if (gigolo_str_equal(scheme, "network"))
		return _("Network");
	else if (gigolo_str_equal(scheme, "archive"))
		return _("Archive");
	else if (gigolo_str_equal(scheme, "gphoto2"))
		return _("Photos");
	else if (gigolo_str_equal(scheme, "custom"))
		return _("Custom Location");

	return NULL;
}
