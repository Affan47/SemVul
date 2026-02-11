dpm_selectfsinpool(int pool_idx, char **excl_host, char **excl_fs, u_signed64 *size, int *fs_idx, int min_free)
{
	struct dpm_fs *elemp;
	int found = 0;
	int i;
	int j;
	struct dpm_pool *poolp;
	u_signed64 reqsize;

	poolp = pools + pool_idx;
	if (poolp->fs_veclen == 0)
		return (-1);
	if (*size == 0)
		reqsize = poolp->defsize;
	else
		reqsize = *size;
	i = poolp->next_elem;
	do {
		elemp = poolp->elemp + *(poolp->fs_vec + i);
		if (excl_host) {
			j = 0;
			while (excl_host[j]) {
				if (strcmp (elemp->server, excl_host[j]) == 0 &&
				    strcmp (elemp->fs, excl_fs[j]) == 0) break;
				j++;
			}
		}
		if (! excl_host || ! excl_host[j])
			if (elemp->status == 0 && elemp->free > 0 &&
			    elemp->free >= reqsize &&
			    ((elemp->free - reqsize) * 100) >= (elemp->capacity * min_free)) {
				found = 1;
				break;
			}
		i++;
		if (i >= poolp->fs_veclen) i = 0;
	} while (i != poolp->next_elem);
	if (! found)
		return (-1);

	poolp->next_elem = i + 1;
	if (poolp->next_elem >= poolp->fs_veclen) poolp->next_elem = 0;
	*size = reqsize;
	*fs_idx = *(poolp->fs_vec + i);
	return (0);
}
