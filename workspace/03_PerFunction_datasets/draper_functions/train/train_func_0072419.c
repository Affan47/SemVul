parseTypeString(const char *str, Oid *type_id, int32 *typmod_p)
{
	StringInfoData buf;
	List	   *raw_parsetree_list;
	SelectStmt *stmt;
	ResTarget  *restarget;
	TypeCast   *typecast;
	TypeName   *typename;
	ErrorContextCallback ptserrcontext;


	if (strspn(str, " \t\n\r\f") == strlen(str))
		goto fail;

	initStringInfo(&buf);
	appendStringInfo(&buf, "SELECT NULL::%s", str);


	ptserrcontext.callback = pts_error_callback;
	ptserrcontext.arg = (void *) str;
	ptserrcontext.previous = error_context_stack;
	error_context_stack = &ptserrcontext;

	raw_parsetree_list = raw_parser(buf.data);

	error_context_stack = ptserrcontext.previous;


	if (list_length(raw_parsetree_list) != 1)
		goto fail;
	stmt = (SelectStmt *) linitial(raw_parsetree_list);
	if (stmt == NULL ||
		!IsA(stmt, SelectStmt) ||
		stmt->distinctClause != NIL ||
		stmt->intoClause != NULL ||
		stmt->fromClause != NIL ||
		stmt->whereClause != NULL ||
		stmt->groupClause != NIL ||
		stmt->havingClause != NULL ||
		stmt->valuesLists != NIL ||
		stmt->sortClause != NIL ||
		stmt->limitOffset != NULL ||
		stmt->limitCount != NULL ||
		stmt->lockingClause != NIL ||
		stmt->op != SETOP_NONE)
		goto fail;
	if (list_length(stmt->targetList) != 1)
		goto fail;
	restarget = (ResTarget *) linitial(stmt->targetList);
	if (restarget == NULL ||
		!IsA(restarget, ResTarget) ||
		restarget->name != NULL ||
		restarget->indirection != NIL)
		goto fail;
	typecast = (TypeCast *) restarget->val;
	if (typecast == NULL ||
		!IsA(typecast, TypeCast) ||
		typecast->arg == NULL ||
		!IsA(typecast->arg, A_Const))
		goto fail;
	typename = typecast->typename;
	if (typename == NULL ||
		!IsA(typename, TypeName))
		goto fail;
	if (typename->setof)
		goto fail;

	*type_id = typenameTypeId(NULL, typename, typmod_p);

	pfree(buf.data);

	return;

fail:
	ereport(ERROR,
			(errcode(ERRCODE_SYNTAX_ERROR),
			 errmsg("invalid type name \"%s\"", str)));
}
