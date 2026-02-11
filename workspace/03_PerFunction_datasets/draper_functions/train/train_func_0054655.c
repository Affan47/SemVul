dpm_findfs(char *server, char *fs, int *pool_idx)
{
	struct dpm_fs *elemp;
	int i;
	int j;

	if (*pool_idx >= 0) {
		elemp = (pools + *pool_idx)->elemp;
		for (j = 0; j < (pools + *pool_idx)->nbelem; j++) {
			if (strcmp (elemp->server, server) == 0 &&
			    strcmp (elemp->fs, fs) == 0) {
				return (j);
			}
			elemp++;
		}
	}

	for (i = 0; i < nbpool; i++) {
		elemp = (pools + i)->elemp;
		for (j = 0; j < (pools + i)->nbelem; j++) {
			if (strcmp (elemp->server, server) == 0 &&
			    strcmp (elemp->fs, fs) == 0) {
				*pool_idx = i;
				return (j);
			}
			elemp++;
		}
	}
	return (-1);
}
