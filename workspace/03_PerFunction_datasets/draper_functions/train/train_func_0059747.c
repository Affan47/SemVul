do_acct_process(struct bsd_acct_struct *acct)
{
	acct_t ac;
	unsigned long flim;
	const struct cred *orig_cred;
	struct file *file = acct->file;


	flim = current->signal->rlim[RLIMIT_FSIZE].rlim_cur;
	current->signal->rlim[RLIMIT_FSIZE].rlim_cur = RLIM_INFINITY;

	orig_cred = override_creds(file->f_cred);


	if (!check_free_space(acct))
		goto out;

	fill_ac(&ac);

	ac.ac_uid = from_kuid_munged(file->f_cred->user_ns, orig_cred->uid);
	ac.ac_gid = from_kgid_munged(file->f_cred->user_ns, orig_cred->gid);
#if ACCT_VERSION == 1 || ACCT_VERSION == 2

	ac.ac_uid16 = ac.ac_uid;
	ac.ac_gid16 = ac.ac_gid;
#endif
#if ACCT_VERSION == 3
	{
		struct pid_namespace *ns = acct->ns;

		ac.ac_pid = task_tgid_nr_ns(current, ns);
		rcu_read_lock();
		ac.ac_ppid = task_tgid_nr_ns(rcu_dereference(current->real_parent),
					     ns);
		rcu_read_unlock();
	}
#endif


	if (file_start_write_trylock(file)) {

		loff_t pos = 0;
		__kernel_write(file, (char *)&ac, sizeof(acct_t), &pos);
		file_end_write(file);
	}
out:
	current->signal->rlim[RLIMIT_FSIZE].rlim_cur = flim;
	revert_creds(orig_cred);
}
