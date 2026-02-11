CommentProc(List *function, List *arguments, char *comment)
{
	Oid			oid;


	oid = LookupFuncNameTypeNames(function, arguments, false);


	if (!pg_proc_ownercheck(oid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_PROC,
					   NameListToString(function));


	CreateComments(oid, ProcedureRelationId, 0, comment);
}
