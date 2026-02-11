pk_backend_what_provides_timeout (gpointer data)
{
	PkBackendJob *job = (PkBackendJob *) data;
	PkBackendDummyJobData *job_data = pk_backend_job_get_user_data (job);

	if (job_data->progress_percentage == 100) {
		if (g_strcmp0 (priv->values[0], "gstreamer0.10(decoder-audio/x-wma)(wmaversion=3)") == 0) {
			pk_backend_job_package (job, PK_INFO_ENUM_AVAILABLE,
						"gstreamer-plugins-bad;0.10.3-5.lvn;i386;available",
						"GStreamer streaming media framework \"bad\" plug-ins");
		} else if (g_strcmp0 (priv->values[0], "gstreamer0.10(decoder-video/x-wma)(wmaversion=3)") == 0) {
			pk_backend_job_package (job, PK_INFO_ENUM_AVAILABLE,
						"gstreamer-plugins-flumpegdemux;0.10.15-5.lvn;i386;available",
						"MPEG demuxer for GStreamer");
		} else {

			if (g_strcmp0 (priv->values[0], "vips-doc") != 0) {
				if (!pk_bitfield_contain (priv->filters, PK_FILTER_ENUM_NOT_INSTALLED)) {
					pk_backend_job_package (job, PK_INFO_ENUM_INSTALLED,
								"evince;0.9.3-5.fc8;i386;installed",
								"PDF Document viewer");
				}
				if (!pk_bitfield_contain (priv->filters, PK_FILTER_ENUM_INSTALLED)) {
					pk_backend_job_package (job, PK_INFO_ENUM_AVAILABLE,
								"scribus;1.3.4-1.fc8;i386;fedora",
								"Scribus is an desktop open source page layout program");
				}
			}
		}
		pk_backend_job_finished (job);
		return FALSE;
	}
	job_data->progress_percentage += 10;
	pk_backend_job_set_percentage (job, job_data->progress_percentage);
	return TRUE;
}
