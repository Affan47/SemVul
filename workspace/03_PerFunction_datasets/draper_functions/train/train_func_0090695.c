aa_task_setrlimit(struct aa_label *label, struct task_struct *task,
		      unsigned int resource, struct rlimit *new_rlim)
{
	struct aa_profile *profile;
	struct aa_label *peer;
	int error = 0;

	rcu_read_lock();
	peer = aa_get_newest_cred_label(__task_cred(task));
	rcu_read_unlock();


	if (label != peer &&
	    !aa_capable(label, CAP_SYS_RESOURCE, SECURITY_CAP_NOAUDIT))
		error = fn_for_each(label, profile,
				audit_resource(profile, resource,
					       new_rlim->rlim_max, EACCES));
	else
		error = fn_for_each_confined(label, profile,
				profile_setrlimit(profile, resource, new_rlim));
	aa_put_label(peer);

	return error;
}
