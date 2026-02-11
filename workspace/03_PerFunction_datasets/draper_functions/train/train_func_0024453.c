copy_job_done (gpointer user_data)
{
	CopyMoveJob *job;

	job = user_data;
	if (job->done_callback) {
		job->done_callback (job->debuting_files,
				    !job_aborted ((CommonJob *) job),
				    job->done_callback_data);
	}


	GHashTableIter iter;
	GFile *file;
	gpointer done;
	g_hash_table_iter_init (&iter, job->debuting_files);
	while (g_hash_table_iter_next (&iter, (gpointer *) &file, &done)) {
		if (GPOINTER_TO_INT (done)) {

            g_object_ref (file);


            log_zeitgeist_event_for_file_no_reply (
                ZEITGEIST_ZG_CREATE_EVENT, file, NULL);
		}
	}


	g_list_free_full (job->files, g_object_unref);
	if (job->destination) {
		g_object_unref (job->destination);
	}
	if (job->desktop_location) {
		g_object_unref (job->desktop_location);
	}
	g_hash_table_unref (job->debuting_files);
	g_free (job->icon_positions);
	g_free (job->target_name);

	g_clear_object (&job->fake_display_source);

	finalize_common ((CommonJob *)job);

	nautilus_file_changes_consume_changes (TRUE);
	return FALSE;
}
