_copyAlterTableCmd(AlterTableCmd *from)
{
	AlterTableCmd *newnode = makeNode(AlterTableCmd);

	COPY_SCALAR_FIELD(subtype);
	COPY_STRING_FIELD(name);
	COPY_NODE_FIELD(def);
	COPY_NODE_FIELD(transform);
	COPY_SCALAR_FIELD(behavior);

	return newnode;
}
