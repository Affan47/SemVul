_copyColumnDef(ColumnDef *from)
{
	ColumnDef  *newnode = makeNode(ColumnDef);

	COPY_STRING_FIELD(colname);
	COPY_NODE_FIELD(typeName);
	COPY_SCALAR_FIELD(inhcount);
	COPY_SCALAR_FIELD(is_local);
	COPY_SCALAR_FIELD(is_not_null);
	COPY_SCALAR_FIELD(storage);
	COPY_NODE_FIELD(raw_default);
	COPY_NODE_FIELD(cooked_default);
	COPY_NODE_FIELD(constraints);

	return newnode;
}
