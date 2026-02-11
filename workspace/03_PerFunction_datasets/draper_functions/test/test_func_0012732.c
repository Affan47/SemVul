_copyCreateTableSpaceStmt(const CreateTableSpaceStmt *from)
{
	CreateTableSpaceStmt *newnode = makeNode(CreateTableSpaceStmt);

	COPY_STRING_FIELD(tablespacename);
	COPY_NODE_FIELD(owner);
	COPY_STRING_FIELD(location);
	COPY_NODE_FIELD(options);

	return newnode;
}
