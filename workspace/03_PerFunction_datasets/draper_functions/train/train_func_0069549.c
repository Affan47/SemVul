step_checkpoint(void)
{
	static int ckpt_run = -1;
	time_t now = time(NULL), ckpt_due;
	ListIterator job_iterator;
	struct job_record *job_ptr;
	ListIterator step_iterator;
	struct step_record *step_ptr;
	time_t event_time;
	uint32_t error_code;
	char *error_msg;
	checkpoint_msg_t ckpt_req;


	if (ckpt_run == -1) {
		char *ckpt_type = slurm_get_checkpoint_type();
		if (strcasecmp(ckpt_type, "checkpoint/none"))
			ckpt_run = 1;
		else
			ckpt_run = 0;
		xfree(ckpt_type);
	}
	if (ckpt_run == 0)
		return;

	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (!IS_JOB_RUNNING(job_ptr))
			continue;
		if (job_ptr->batch_flag &&
		    (job_ptr->ckpt_interval != 0)) {
			ckpt_due = job_ptr->ckpt_time +
				   (job_ptr->ckpt_interval * 60);
			if (ckpt_due > now)
				continue;


			ckpt_due = job_ptr->start_time +
				   (job_ptr->ckpt_interval * 60);
			if (ckpt_due > now)
				continue;

			ckpt_req.op = CHECK_CREATE;
			ckpt_req.data = 0;
			ckpt_req.job_id = job_ptr->job_id;
			ckpt_req.step_id = SLURM_BATCH_SCRIPT;
			ckpt_req.image_dir = NULL;
			job_checkpoint(&ckpt_req, getuid(), -1,
				       (uint16_t)NO_VAL);
			job_ptr->ckpt_time = now;
			last_job_update = now;
			continue;
		}
		step_iterator = list_iterator_create (job_ptr->step_list);
		if (!step_iterator)
			fatal("list_iterator_create: malloc failure");
		while ((step_ptr = (struct step_record *)
				list_next (step_iterator))) {
			char *image_dir = NULL;
			if (step_ptr->ckpt_interval == 0)
				continue;
			ckpt_due = step_ptr->ckpt_time +
				   (step_ptr->ckpt_interval * 60);
			if (ckpt_due > now)
				continue;


			ckpt_due = step_ptr->start_time +
				   (step_ptr->ckpt_interval * 60);
			if (ckpt_due > now)
				continue;

			step_ptr->ckpt_time = now;
			last_job_update = now;
			image_dir = xstrdup(step_ptr->ckpt_dir);
			xstrfmtcat(image_dir, "/%u.%u", job_ptr->job_id,
				   step_ptr->step_id);
			(void) checkpoint_op(job_ptr->job_id,
					     step_ptr->step_id,
					     step_ptr, CHECK_CREATE, 0,
					     image_dir, &event_time,
					     &error_code, &error_msg);
			xfree(image_dir);
		}
		list_iterator_destroy (step_iterator);
	}
	list_iterator_destroy(job_iterator);
}
