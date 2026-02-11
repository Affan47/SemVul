gfarm_ldap_xattr_remove(struct db_xattr_arg *arg)
{
	gfarm_error_t e;
	struct gfarm_ldap_xattr_get_info_key key;

	if (arg->xmlMode)
		return (GFARM_ERR_OPERATION_NOT_SUPPORTED);

	key.inumber = arg->inum;
	key.attrname = arg->attrname;

	e = gfarm_ldap_generic_info_remove(&key, &gfarm_ldap_xattr_info_ops);
	free(arg);
	return (e);
}
