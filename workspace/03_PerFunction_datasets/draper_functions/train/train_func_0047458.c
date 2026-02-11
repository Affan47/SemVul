install_packages (GstTool *tool, gboolean install_nfs, gboolean install_smb)
{
	gchar **packages;
	gboolean retval;
	gint i = 0;

	if (!install_nfs && !install_smb)
		return FALSE;

	packages = g_new0 (gchar*, 3);

	if (install_nfs)
		packages[i++] = g_strdup ("nfs-kernel-server");

	if (install_smb)
		packages[i++] = g_strdup ("samba");

	retval = gst_packages_install (GTK_WINDOW (tool->main_dialog), packages);
	g_strfreev (packages);

	return retval;
}
