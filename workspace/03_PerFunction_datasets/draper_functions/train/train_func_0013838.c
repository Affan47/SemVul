role_val_to_name(unsigned int val)
{
	struct val_to_name v;
	int rc;

	v.val = val;
	rc = hashtab_map(policydbp->p_roles.table, role_val_to_name_helper, &v);
	if (rc)
		return v.name;
	return NULL;
}
