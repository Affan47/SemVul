_get_fairshare_priority( struct job_record *job_ptr)
{
	slurmdb_association_rec_t *job_assoc =
		(slurmdb_association_rec_t *)job_ptr->assoc_ptr;
	slurmdb_association_rec_t *fs_assoc = NULL;
	double priority_fs = 0.0;
	assoc_mgr_lock_t locks = { READ_LOCK, NO_LOCK,
				   NO_LOCK, NO_LOCK, NO_LOCK };

	if (!calc_fairshare)
		return 0;

	if (!job_assoc) {
		error("Job %u has no association.  Unable to "
		      "compute fairshare.", job_ptr->job_id);
		return 0;
	}

	fs_assoc = job_assoc;

	assoc_mgr_lock(&locks);


	while ((fs_assoc->shares_raw == SLURMDB_FS_USE_PARENT)
	       && fs_assoc->usage->parent_assoc_ptr
	       && (fs_assoc != assoc_mgr_root_assoc)) {
		fs_assoc = fs_assoc->usage->parent_assoc_ptr;
	}

	if (fuzzy_equal(fs_assoc->usage->usage_efctv, NO_VAL))
		priority_p_set_assoc_usage(fs_assoc);


	priority_fs = 0;
	if (flags & PRIORITY_FLAGS_TICKET_BASED) {
		if (fs_assoc->usage->active_seqno ==
		    assoc_mgr_root_assoc->usage->active_seqno && max_tickets) {
			priority_fs = (double) fs_assoc->usage->tickets /
				      max_tickets;
		}
		if (priority_debug) {
			info("Fairshare priority of job %u for user %s in acct"
			     " %s is %f",
			     job_ptr->job_id, job_assoc->user, job_assoc->acct,
			     priority_fs);
		}
	} else {
		priority_fs = priority_p_calc_fs_factor(
				fs_assoc->usage->usage_efctv,
				(long double)fs_assoc->usage->shares_norm);
		if (priority_debug) {
			info("Fairshare priority of job %u for user %s in acct"
			     " %s is 2**(-%Lf/%f) = %f",
			     job_ptr->job_id, job_assoc->user, job_assoc->acct,
			     fs_assoc->usage->usage_efctv,
			     fs_assoc->usage->shares_norm, priority_fs);
		}
	}
	assoc_mgr_unlock(&locks);

	return priority_fs;
}
