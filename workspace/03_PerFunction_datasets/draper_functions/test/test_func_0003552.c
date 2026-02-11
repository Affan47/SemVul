qpol_type_get_ispermissive(const qpol_policy_t * policy, const qpol_type_t * datum, unsigned char *ispermissive)
{
	if (policy == NULL || datum == NULL || ispermissive == NULL) {
		if (ispermissive != NULL)
			*ispermissive = 0;
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}
#ifdef HAVE_SEPOL_PERMISSIVE_TYPES


	uint32_t value;
	if (qpol_type_get_value(policy, datum, &value) < 0) {
		return STATUS_ERR;
	}
	policydb_t *p = &policy->p->p;


	*ispermissive = ebitmap_get_bit(&p->permissive_map, value);
#else
	*ispermissive = 0;
#endif

	return STATUS_SUCCESS;
}
