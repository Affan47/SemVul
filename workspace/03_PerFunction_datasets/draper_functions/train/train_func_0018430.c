mail_job_info (struct job_record *job_ptr, uint16_t mail_type)
{
	char job_time[128];
	mail_info_t *mi = _mail_alloc();

	if (!job_ptr->mail_user)
		mi->user_name = uid_to_string((uid_t)job_ptr->user_id);
	else
		mi->user_name = xstrdup(job_ptr->mail_user);

	_set_job_time(job_ptr, mail_type, job_time, sizeof(job_time));
	mi->message = xstrdup_printf("SLURM Job_id=%u Name=%s %s%s",
				     job_ptr->job_id, job_ptr->name,
				     _mail_type_str(mail_type), job_time);

	debug("email msg to %s: %s", mi->user_name, mi->message);

	slurm_mutex_lock(&mail_mutex);
	if (!mail_list) {
		mail_list = list_create(_mail_free);
		if (!mail_list)
			fatal("list_create failed");
	}
	(void) list_enqueue(mail_list, (void *) mi);
	slurm_mutex_unlock(&mail_mutex);
	return;
}
