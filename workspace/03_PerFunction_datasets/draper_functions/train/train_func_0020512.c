CommentTablespace(List *qualname, char *comment)
{
	char	   *tablespace;
	Oid			oid;

	if (list_length(qualname) != 1)
		ereport(ERROR,
				(errcode(ERRCODE_SYNTAX_ERROR),
				 errmsg("tablespace name may not be qualified")));
	tablespace = strVal(linitial(qualname));

	oid = get_tablespace_oid(tablespace);
	if (!OidIsValid(oid))
	{
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("tablespace \"%s\" does not exist", tablespace)));
		return;
	}


	if (!pg_tablespace_ownercheck(oid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_TABLESPACE, tablespace);


	CreateSharedComments(oid, TableSpaceRelationId, comment);
}
