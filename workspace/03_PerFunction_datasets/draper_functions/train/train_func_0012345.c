ndmca_op_init_labels (struct ndm_session *sess)
{
	struct ndm_control_agent *ca = &sess->control_acb;
	struct ndm_job_param *	job = &ca->job;
	struct ndm_media_table *mtab = &job->media_tab;
	int			n_media = mtab->n_media;
	struct ndmmedia *	me;
	int			rc, i, errors;

	ca->tape_mode = NDMP9_TAPE_RDWR_MODE;
	ca->is_label_op = 1;

	if (n_media <= 0) {
		ndmalogf (sess, 0, 0, "No media entries in table");
		return -1;
	}

	errors = 0;
	for (i = 0; i < n_media; i++) {
		me = &mtab->media[i];

		if (me->valid_label)
			continue;

		ndmalogf (sess, 0, 0, "media #%d missing a label", i+1);
		errors++;
	}
	if (errors)
		return -1;

	rc = ndmca_op_robot_startup (sess, 1);
	if (rc) return rc;

	rc = ndmca_connect_tape_agent (sess);
	if (rc) {
		ndmconn_destruct (sess->plumb.tape);
		return rc;
	}

	for (i = 0; i < n_media; i++) {
		ca->cur_media_ix = i;

		me = &mtab->media[i];

		rc = ndmca_media_load_current (sess);
		if (rc) {

			continue;
		}

		rc = ndmca_media_write_label (sess, 'm', me->label);
		if (rc) {
			ndmalogf (sess, 0, 0, "failed label write");
		}

		ndmca_media_write_filemarks(sess);
		ndmca_media_unload_current (sess);
	}

	return rc;
}
