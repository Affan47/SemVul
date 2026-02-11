brasero_mkisofs_base_write_graft (BraseroMkisofsBase *base,
				  const gchar *uri,
				  const gchar *disc_path,
				  GError **error)
{
	gchar *graft_point;
	BraseroBurnResult result;


	graft_point = _build_graft_point (uri, disc_path);
	if (!graft_point) {
		g_set_error (error,
			     BRASERO_BURN_ERROR,
			     BRASERO_BURN_ERROR_GENERAL,


			     _("An internal error occurred"));
		return BRASERO_BURN_ERR;
	}

	result = _write_line (base->grafts_fd, graft_point, error);
	g_free (graft_point);
	if (result != BRASERO_BURN_OK)
		return result;

	return BRASERO_BURN_OK;
}
