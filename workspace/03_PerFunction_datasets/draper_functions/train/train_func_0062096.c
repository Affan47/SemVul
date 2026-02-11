qpol_context_get_role(const qpol_policy_t * policy, const qpol_context_t * context, const qpol_role_t ** role)
{
	policydb_t *db = NULL;
	context_struct_t *internal_context = NULL;

	if (role != NULL)
		*role = NULL;

	if (policy == NULL || context == NULL || role == NULL) {
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	internal_context = (context_struct_t *) context;
	db = &policy->p->p;

	*role = (qpol_role_t *) db->role_val_to_struct[internal_context->role - 1];

	return STATUS_SUCCESS;
}
