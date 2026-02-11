coerce_to_common_type(ParseState *pstate, Node *node,
					  Oid targetTypeId, const char *context)
{
	Oid			inputTypeId = exprType(node);

	if (inputTypeId == targetTypeId)
		return node;
	if (can_coerce_type(1, &inputTypeId, &targetTypeId, COERCION_IMPLICIT))
		node = coerce_type(pstate, node, inputTypeId, targetTypeId, -1,
						   COERCION_IMPLICIT, COERCE_IMPLICIT_CAST, -1);
	else
		ereport(ERROR,
				(errcode(ERRCODE_CANNOT_COERCE),

				 errmsg("%s could not convert type %s to %s",
						context,
						format_type_be(inputTypeId),
						format_type_be(targetTypeId)),
				 parser_errposition(pstate, exprLocation(node))));
	return node;
}
