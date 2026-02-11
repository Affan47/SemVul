pk_backend_get_repo_list (PkBackend *backend, PkBackendJob *job, PkBitfield filters)
{
	pk_backend_job_set_status (job, PK_STATUS_ENUM_QUERY);
	pk_backend_job_repo_detail (job, "fedora",
				    "Fedora - 9", priv->repo_enabled_fedora);
	if (!pk_bitfield_contain (filters, PK_FILTER_ENUM_NOT_DEVELOPMENT)) {
		pk_backend_job_repo_detail (job, "development",
					    "Fedora - Development",
					    priv->repo_enabled_devel);
	}
	pk_backend_job_repo_detail (job, "livna-development",
				    "Livna for Fedora Core 8 - i386 - Development Tree",
				    priv->repo_enabled_livna);
	pk_backend_job_finished (job);
}
