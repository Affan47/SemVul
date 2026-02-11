dpm_get_fs_status (char *server, char *fs, int *status)
{
	struct dpm_fs *elemp;
	int fs_idx;
	int pool_idx = -1;

	if (Cthread_mutex_lock (&poolconf_mutex) < 0)
		return (-1);
	if ((fs_idx = dpm_findfs (server, fs, &pool_idx)) < 0) {
		(void) Cthread_mutex_unlock (&poolconf_mutex);
		return (-1);
	}
	elemp = (pools + pool_idx)->elemp + fs_idx;
	*status = elemp->status;
	(void) Cthread_mutex_unlock (&poolconf_mutex);
	return (0);
}
