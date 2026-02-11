_scan_slurm_job_list(void)
{
	struct job_record *job_ptr;
	struct gs_part *p_ptr;
	int i;
	ListIterator job_iterator;

	if (!job_list) {
		if (slurmctld_conf.debug_flags & DEBUG_FLAG_GANG)
			info("gang: _scan_slurm_job_list: job_list NULL");
		return;
	}
	if (slurmctld_conf.debug_flags & DEBUG_FLAG_GANG)
		info("gang: _scan_slurm_job_list: job_list exists...");
	job_iterator = list_iterator_create(job_list);
	while ((job_ptr = (struct job_record *) list_next(job_iterator))) {
		if (slurmctld_conf.debug_flags & DEBUG_FLAG_GANG) {
			info("gang: _scan_slurm_job_list: checking job %u",
			    job_ptr->job_id);
		}
		if (IS_JOB_PENDING(job_ptr))
			continue;
		if (IS_JOB_SUSPENDED(job_ptr) && (job_ptr->priority == 0))
			continue;

		if (IS_JOB_SUSPENDED(job_ptr) || IS_JOB_RUNNING(job_ptr)) {

			p_ptr = list_find_first(gs_part_list, _find_gs_part,
						job_ptr->partition);
			if (!p_ptr)
				continue;
			i = _find_job_index(p_ptr, job_ptr->job_id);
			if (i >= 0)
				continue;


			if (IS_JOB_SUSPENDED(job_ptr)) {


				_resume_job(job_ptr->job_id);
			}

			_add_job_to_part(p_ptr, job_ptr);
			continue;
		}


		p_ptr = list_find_first(gs_part_list, _find_gs_part,
					job_ptr->partition);
		if (!p_ptr)
			continue;
		_remove_job_from_part(job_ptr->job_id, p_ptr, false);
	}
	list_iterator_destroy(job_iterator);


	_update_all_active_rows();

	return;
}
