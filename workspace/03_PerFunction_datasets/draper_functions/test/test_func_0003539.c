ExecuteGrantStmt(GrantStmt *stmt)
{
	InternalGrant istmt;
	ListCell   *cell;
	char	   *errormsg;
	AclMode		all_privileges;


	istmt.is_grant = stmt->is_grant;
	istmt.objtype = stmt->objtype;
	istmt.objects = objectNamesToOids(stmt->objtype, stmt->objects);


	istmt.grantees = NIL;

	istmt.grant_option = stmt->grant_option;
	istmt.behavior = stmt->behavior;


	foreach(cell, stmt->grantees)
	{
		PrivGrantee *grantee = (PrivGrantee *) lfirst(cell);

		if (grantee->rolname == NULL)
			istmt.grantees = lappend_oid(istmt.grantees, ACL_ID_PUBLIC);
		else
			istmt.grantees =
				lappend_oid(istmt.grantees,
							get_roleid_checked(grantee->rolname));
	}


	switch (stmt->objtype)
	{


		case ACL_OBJECT_RELATION:
			all_privileges = ACL_ALL_RIGHTS_RELATION | ACL_ALL_RIGHTS_SEQUENCE;
			errormsg = _("invalid privilege type %s for relation");
			break;
		case ACL_OBJECT_SEQUENCE:
			all_privileges = ACL_ALL_RIGHTS_SEQUENCE;
			errormsg = _("invalid privilege type %s for sequence");
			break;
		case ACL_OBJECT_DATABASE:
			all_privileges = ACL_ALL_RIGHTS_DATABASE;
			errormsg = _("invalid privilege type %s for database");
			break;
		case ACL_OBJECT_FUNCTION:
			all_privileges = ACL_ALL_RIGHTS_FUNCTION;
			errormsg = _("invalid privilege type %s for function");
			break;
		case ACL_OBJECT_LANGUAGE:
			all_privileges = ACL_ALL_RIGHTS_LANGUAGE;
			errormsg = _("invalid privilege type %s for language");
			break;
		case ACL_OBJECT_NAMESPACE:
			all_privileges = ACL_ALL_RIGHTS_NAMESPACE;
			errormsg = _("invalid privilege type %s for schema");
			break;
		case ACL_OBJECT_TABLESPACE:
			all_privileges = ACL_ALL_RIGHTS_TABLESPACE;
			errormsg = _("invalid privilege type %s for tablespace");
			break;
		default:

			all_privileges = ACL_NO_RIGHTS;
			errormsg = NULL;
			elog(ERROR, "unrecognized GrantStmt.objtype: %d",
				 (int) stmt->objtype);
	}

	if (stmt->privileges == NIL)
	{
		istmt.all_privs = true;


		istmt.privileges = ACL_NO_RIGHTS;
	}
	else
	{
		istmt.all_privs = false;
		istmt.privileges = ACL_NO_RIGHTS;

		foreach(cell, stmt->privileges)
		{
			char	   *privname = strVal(lfirst(cell));
			AclMode		priv = string_to_privilege(privname);

			if (priv & ~((AclMode) all_privileges))
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_GRANT_OPERATION),
						 errmsg(errormsg,
								privilege_to_string(priv))));

			istmt.privileges |= priv;
		}
	}

	ExecGrantStmt_oids(&istmt);
}
