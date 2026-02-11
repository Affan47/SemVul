sigio_perm(struct task_struct *p,
                             struct fown_struct *fown, int sig)
{
	const struct cred *cred;
	int ret;

	rcu_read_lock();
	cred = __task_cred(p);
	ret = ((uid_eq(fown->euid, GLOBAL_ROOT_UID) ||
		uid_eq(fown->euid, cred->suid) || uid_eq(fown->euid, cred->uid) ||
		uid_eq(fown->uid,  cred->suid) || uid_eq(fown->uid,  cred->uid)) &&
	       !security_file_send_sigiotask(p, fown, sig));
	rcu_read_unlock();
	return ret;
}
