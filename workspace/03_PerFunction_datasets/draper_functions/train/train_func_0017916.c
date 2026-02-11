ndmca_media_verify (struct ndm_session *sess)
{
	struct ndm_control_agent *ca = &sess->control_acb;
	struct ndm_job_param *	job = &ca->job;
	int			rc;

	if (job->have_robot)
		return 0;

	rc = ndmca_robot_verify_media (sess);
	if (rc == 0)
		return rc;

	ndmca_media_tattle (sess);

	return -1;
}
