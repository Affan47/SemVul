pk_backend_install_thread (PkBackendJob *job, GVariant *params, gpointer user_data)
{
	gchar **package_ids;
	PkBitfield transaction_flags;
	PkBackendDummyJobData *job_data = pk_backend_job_get_user_data (job);

	g_variant_get (params, "(t^a&s)",
		       &transaction_flags,
		       &package_ids);

	while (TRUE) {


		if (g_cancellable_is_cancelled (job_data->cancellable)) {
			pk_backend_job_error_code (job,
						   PK_ERROR_ENUM_TRANSACTION_CANCELLED,
						   "The task was stopped successfully");
			pk_backend_job_finished (job);
			break;
		}

		if (job_data->progress_percentage == 100) {
			pk_backend_job_finished (job);
			break;
		}

		if (job_data->progress_percentage == 30) {
			pk_backend_job_set_allow_cancel (job, FALSE);
			pk_backend_job_package (job, PK_INFO_ENUM_INSTALLING,
						"gtkhtml2;2.19.1-4.fc8;i386;fedora",
						"An HTML widget for GTK+ 2.0");
			pk_backend_job_set_status (job, PK_STATUS_ENUM_INSTALL);
		}

		if (job_data->progress_percentage == 50) {
			pk_backend_job_package (job, PK_INFO_ENUM_INSTALLING,
						"gtkhtml2-devel;2.19.1-0.fc8;i386;fedora",
						"Devel files for gtkhtml");

			pk_backend_job_package (job, PK_INFO_ENUM_INSTALLING,
						"gtkhtml2-devel;2.19.1-0.fc8;i386;fedora", NULL);
			pk_backend_job_set_status (job, PK_STATUS_ENUM_INSTALL);
		}

		job_data->progress_percentage += 1;
		pk_backend_job_set_percentage (job, job_data->progress_percentage);


		g_usleep (100000);
	}


	priv->fake_db_locked = FALSE;
	pk_backend_job_set_locked (job, FALSE);
}
