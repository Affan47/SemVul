pk_backend_install_signature (PkBackend *backend, PkBackendJob *job, PkSigTypeEnum type,
			   const gchar *key_id, const gchar *package_id)
{
	pk_backend_job_set_status (job, PK_STATUS_ENUM_INSTALL);
	if (type == PK_SIGTYPE_ENUM_GPG &&

	    g_strcmp0 (key_id, "BB7576AC") == 0) {
		g_debug ("installed signature %s for %s", key_id, package_id);
		priv->has_signature = TRUE;
	} else {
		pk_backend_job_error_code (job, PK_ERROR_ENUM_GPG_FAILURE,
					   "GPG key %s not recognised for package_id %s",
					   key_id, package_id);
	}
	pk_backend_job_finished (job);
}
