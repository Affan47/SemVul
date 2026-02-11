brasero_vcd_imager_read_stdout (BraseroProcess *process,
				const gchar *line)
{
	gint percent = 0;
	guint track_num = 0;
	BraseroVcdImagerPrivate *priv;

	priv = BRASERO_VCD_IMAGER_PRIVATE (process);

	if (sscanf (line, "#scan[track-%d]: %*d/%*d (%d)", &track_num, &percent) == 2) {
		brasero_job_start_progress (BRASERO_JOB (process), FALSE);
		brasero_job_set_progress (BRASERO_JOB (process),
					  (gdouble) ((gdouble) percent) /
					  100.0 /
					  (gdouble) (priv->num_tracks + 1) +
					  (gdouble) (track_num) /
					  (gdouble) (priv->num_tracks + 1));
	}
	else if (sscanf (line, "#write[%*d/%*d]: %*d/%*d (%d)", &percent) == 1) {
		gdouble progress;


		brasero_job_start_progress (BRASERO_JOB (process), FALSE);
		progress = (gdouble) ((gdouble) percent) /
			   100.0 /
			   (gdouble) (priv->num_tracks + 1) +
			   (gdouble) (priv->num_tracks) /
			   (gdouble) (priv->num_tracks + 1);

		if (progress > 1.0)
			progress = 1.0;

		brasero_job_set_progress (BRASERO_JOB (process), progress);
	}

	return BRASERO_BURN_OK;
}
