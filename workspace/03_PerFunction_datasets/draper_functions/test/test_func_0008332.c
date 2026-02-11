CopyCreateStmtFields(CreateStmt *from, CreateStmt *newnode)
{
	COPY_NODE_FIELD(relation);
	COPY_NODE_FIELD(tableElts);
	COPY_NODE_FIELD(inhRelations);
	COPY_NODE_FIELD(ofTypename);
	COPY_NODE_FIELD(constraints);
	COPY_NODE_FIELD(options);
	COPY_SCALAR_FIELD(oncommit);
	COPY_STRING_FIELD(tablespacename);
	COPY_SCALAR_FIELD(if_not_exists);
}
