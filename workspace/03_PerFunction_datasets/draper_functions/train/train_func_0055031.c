qpol_policy_get_policy_version(const qpol_policy_t * policy, unsigned int *version)
{
	policydb_t *db;

	if (version != NULL)
		*version = 0;

	if (policy == NULL || version == NULL) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	db = &policy->p->p;

	*version = db->policyvers;

	return STATUS_SUCCESS;
}
