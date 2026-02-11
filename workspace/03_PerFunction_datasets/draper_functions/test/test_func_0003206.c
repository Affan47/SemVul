smack_bprm_secureexec(struct linux_binprm *bprm)
{
	struct task_smack *tsp = current_security();

	if (tsp->smk_task != tsp->smk_forked)
		return 1;

	return 0;
}
