GrantRole(GrantRoleStmt *stmt)
{
	Relation	pg_authid_rel;
	Oid			grantor;
	List	   *grantee_ids;
	ListCell   *item;

	if (stmt->grantor)
		grantor = get_roleid_checked(stmt->grantor);
	else
		grantor = GetUserId();

	grantee_ids = roleNamesToIds(stmt->grantee_roles);


	pg_authid_rel = heap_open(AuthIdRelationId, AccessShareLock);


	foreach(item, stmt->granted_roles)
	{
		char	   *rolename = strVal(lfirst(item));
		Oid			roleid = get_roleid_checked(rolename);

		if (stmt->is_grant)
			AddRoleMems(rolename, roleid,
						stmt->grantee_roles, grantee_ids,
						grantor, stmt->admin_opt);
		else
			DelRoleMems(rolename, roleid,
						stmt->grantee_roles, grantee_ids,
						stmt->admin_opt);
	}


	heap_close(pg_authid_rel, NoLock);


	auth_file_update_needed();
}
