nfsd4_cltrack_grace_start(time_t grace_start)
{
	int copied;
	size_t len;
	char *result;


	len = strlen(GRACE_START_ENV_PREFIX) + 22 + 1;

	result = kmalloc(len, GFP_KERNEL);
	if (!result)
		return result;

	copied = snprintf(result, len, GRACE_START_ENV_PREFIX "%ld",
				grace_start);
	if (copied >= len) {

		kfree(result);
		return NULL;
	}

	return result;
}
