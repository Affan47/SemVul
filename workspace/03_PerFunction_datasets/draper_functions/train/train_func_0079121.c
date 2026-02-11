qpol_policy_get_bool_by_name(const qpol_policy_t * policy, const char *name, qpol_bool_t ** datum)
{
	hashtab_datum_t internal_datum;
	policydb_t *db;

	if (policy == NULL || name == NULL || datum == NULL) {
		if (datum != NULL)
			*datum = NULL;
		ERR(policy, "%s", strerror(EINVAL));
		errno = EINVAL;
		return STATUS_ERR;
	}

	db = &policy->p->p;
	internal_datum = hashtab_search(db->p_bools.table, (const hashtab_key_t)name);
	if (internal_datum == NULL) {
		ERR(policy, "could not find datum for bool %s", name);
		*datum = NULL;
		errno = ENOENT;
		return STATUS_ERR;
	}
	*datum = (qpol_bool_t *) internal_datum;

	return STATUS_SUCCESS;
}
