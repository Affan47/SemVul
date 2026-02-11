_copyCreateConversionStmt(CreateConversionStmt *from)
{
	CreateConversionStmt *newnode = makeNode(CreateConversionStmt);

	COPY_NODE_FIELD(conversion_name);
	COPY_STRING_FIELD(for_encoding_name);
	COPY_STRING_FIELD(to_encoding_name);
	COPY_NODE_FIELD(func_name);
	COPY_SCALAR_FIELD(def);

	return newnode;
}
