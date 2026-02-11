_job_init_task_info(stepd_step_rec_t *job, uint32_t *gtid,
		    char *ifname, char *ofname, char *efname)
{
	int          i;
	char        *in, *out, *err;

	if (job->node_tasks == 0) {
		error("User requested launch of zero tasks!");
		job->task = NULL;
		return;
	}

	job->task = (stepd_step_task_info_t **)
		xmalloc(job->node_tasks * sizeof(stepd_step_task_info_t *));

	for (i = 0; i < job->node_tasks; i++){
		in = _expand_stdio_filename(ifname, gtid[i], job);
		out = _expand_stdio_filename(ofname, gtid[i], job);
		err = _expand_stdio_filename(efname, gtid[i], job);

		job->task[i] = task_info_create(i, gtid[i], in, out, err);

		if (job->multi_prog) {
			multi_prog_get_argv(job->argv[1], job->env, gtid[i],
					    &job->task[i]->argc,
					    &job->task[i]->argv,
					    job->argc, job->argv);
		} else {
			job->task[i]->argc = job->argc;
			job->task[i]->argv = job->argv;
		}
	}
}
