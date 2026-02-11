init_stat_file(struct stat_session *session)
{
	if (!stat_dir && tracing_stat_init())
		return -ENODEV;

	session->file = tracefs_create_file(session->ts->name, 0644,
					    stat_dir,
					    session, &tracing_stat_fops);
	if (!session->file)
		return -ENOMEM;
	return 0;
}
