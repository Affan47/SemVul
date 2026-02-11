dhcp_lease_get (omapi_object_t **lp,
			     const char *file, int line)
{
	struct lease **lease = (struct lease **)lp;
	struct lease *lt;

	if (free_leases) {
		lt = free_leases;
		free_leases = lt -> next;
		*lease = lt;
		return ISC_R_SUCCESS;
	}
	return ISC_R_NOMEMORY;
}
