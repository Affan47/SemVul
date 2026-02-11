_destroy_local_resv_usage(void *object)
{
	local_resv_usage_t *r_usage = (local_resv_usage_t *)object;
	if (r_usage) {
		if (r_usage->local_assocs)
			list_destroy(r_usage->local_assocs);
		xfree(r_usage);
	}
}
