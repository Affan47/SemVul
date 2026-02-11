_equalCopyStmt(const CopyStmt *a, const CopyStmt *b)
{
	COMPARE_NODE_FIELD(relation);
	COMPARE_NODE_FIELD(query);
	COMPARE_NODE_FIELD(attlist);
	COMPARE_SCALAR_FIELD(is_from);
	COMPARE_SCALAR_FIELD(is_program);
	COMPARE_STRING_FIELD(filename);
	COMPARE_NODE_FIELD(options);

	return true;
}
