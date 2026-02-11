ATPrepAddOids(List **wqueue, Relation rel, bool recurse, AlterTableCmd *cmd, LOCKMODE lockmode)
{

	if (cmd->def == NULL)
	{
		ColumnDef  *cdef = makeNode(ColumnDef);

		cdef->colname = pstrdup("oid");
		cdef->typeName = makeTypeNameFromOid(OIDOID, -1);
		cdef->inhcount = 0;
		cdef->is_local = true;
		cdef->is_not_null = true;
		cdef->storage = 0;
		cdef->location = -1;
		cmd->def = (Node *) cdef;
	}
	ATPrepAddColumn(wqueue, rel, recurse, false, false, cmd, lockmode);

	if (recurse)
		cmd->subtype = AT_AddOidsRecurse;
}
