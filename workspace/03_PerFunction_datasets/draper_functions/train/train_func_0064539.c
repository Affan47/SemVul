_copyRangeVar(RangeVar *from)
{
	RangeVar   *newnode = makeNode(RangeVar);

	COPY_STRING_FIELD(catalogname);
	COPY_STRING_FIELD(schemaname);
	COPY_STRING_FIELD(relname);
	COPY_SCALAR_FIELD(inhOpt);
	COPY_SCALAR_FIELD(istemp);
	COPY_NODE_FIELD(alias);

	return newnode;
}
