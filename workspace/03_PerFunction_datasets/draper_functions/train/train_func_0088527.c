restrict_and_check_grant(bool is_grant, AclMode avail_goptions, bool all_privs,
						 AclMode privileges, Oid objectId, Oid grantorId,
						 AclObjectKind objkind, const char *objname,
						 AttrNumber att_number, const char *colname)
{
	AclMode		this_privileges;
	AclMode		whole_mask;

	switch (objkind)
	{
		case ACL_KIND_COLUMN:
			whole_mask = ACL_ALL_RIGHTS_COLUMN;
			break;
		case ACL_KIND_CLASS:
			whole_mask = ACL_ALL_RIGHTS_RELATION;
			break;
		case ACL_KIND_SEQUENCE:
			whole_mask = ACL_ALL_RIGHTS_SEQUENCE;
			break;
		case ACL_KIND_DATABASE:
			whole_mask = ACL_ALL_RIGHTS_DATABASE;
			break;
		case ACL_KIND_PROC:
			whole_mask = ACL_ALL_RIGHTS_FUNCTION;
			break;
		case ACL_KIND_LANGUAGE:
			whole_mask = ACL_ALL_RIGHTS_LANGUAGE;
			break;
		case ACL_KIND_NAMESPACE:
			whole_mask = ACL_ALL_RIGHTS_NAMESPACE;
			break;
		case ACL_KIND_TABLESPACE:
			whole_mask = ACL_ALL_RIGHTS_TABLESPACE;
			break;
		case ACL_KIND_FDW:
			whole_mask = ACL_ALL_RIGHTS_FDW;
			break;
		case ACL_KIND_FOREIGN_SERVER:
			whole_mask = ACL_ALL_RIGHTS_FOREIGN_SERVER;
			break;
		default:
			elog(ERROR, "unrecognized object kind: %d", objkind);

			return ACL_NO_RIGHTS;
	}


	if (avail_goptions == ACL_NO_RIGHTS)
	{
		if (pg_aclmask(objkind, objectId, att_number, grantorId,
					   whole_mask | ACL_GRANT_OPTION_FOR(whole_mask),
					   ACLMASK_ANY) == ACL_NO_RIGHTS)
		{
			if (objkind == ACL_KIND_COLUMN && colname)
				aclcheck_error_col(ACLCHECK_NO_PRIV, objkind, objname, colname);
			else
				aclcheck_error(ACLCHECK_NO_PRIV, objkind, objname);
		}
	}


	this_privileges = privileges & ACL_OPTION_TO_PRIVS(avail_goptions);
	if (is_grant)
	{
		if (this_privileges == 0)
	   	{
			if (objkind == ACL_KIND_COLUMN && colname)
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_GRANTED),
						 errmsg("no privileges were granted for column \"%s\" of relation \"%s\"",
								colname, objname)));
			else
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_GRANTED),
						 errmsg("no privileges were granted for \"%s\"",
								objname)));
		}
		else if (!all_privs && this_privileges != privileges)
		{
			if (objkind == ACL_KIND_COLUMN && colname)
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_GRANTED),
						 errmsg("not all privileges were granted for column \"%s\" of relation \"%s\"",
								colname, objname)));
			else
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_GRANTED),
						 errmsg("not all privileges were granted for \"%s\"",
								objname)));
		}
	}
	else
	{
		if (this_privileges == 0)
		{
			if (objkind == ACL_KIND_COLUMN && colname)
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_REVOKED),
						 errmsg("no privileges could be revoked for column \"%s\" of relation \"%s\"",
								colname, objname)));
			else
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_REVOKED),
						 errmsg("no privileges could be revoked for \"%s\"",
								objname)));
		}
		else if (!all_privs && this_privileges != privileges)
		{
			if (objkind == ACL_KIND_COLUMN && colname)
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_REVOKED),
						 errmsg("not all privileges could be revoked for column \"%s\" of relation \"%s\"",
								colname, objname)));
			else
				ereport(WARNING,
						(errcode(ERRCODE_WARNING_PRIVILEGE_NOT_REVOKED),
						 errmsg("not all privileges could be revoked for \"%s\"",
								objname)));
		}
	}

	return this_privileges;
}
