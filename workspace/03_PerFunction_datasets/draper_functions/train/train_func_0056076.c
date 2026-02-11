xmms_build_path (const char *first, ...)
{
	va_list ap;
	gchar confdir[XMMS_PATH_MAX];
	gchar *ret, **vargv, **argv;

	g_return_val_if_fail (first, NULL);

	xmms_userconfdir_get (confdir, XMMS_PATH_MAX);

	va_start (ap, first);
	vargv = xmms_valist_to_strlist (first, ap);
	va_end (ap);

	argv = xmms_strlist_prepend_copy (vargv, confdir);

	ret = g_build_pathv (G_DIR_SEPARATOR_S, argv);
	xmms_strlist_destroy (vargv);
	xmms_strlist_destroy (argv);
	return ret;
}
