ATSimpleRecursion(List **wqueue, Relation rel,
				  AlterTableCmd *cmd, bool recurse, LOCKMODE lockmode)
{


	if (recurse &&
		(rel->rd_rel->relkind == RELKIND_RELATION ||
		 rel->rd_rel->relkind == RELKIND_FOREIGN_TABLE))
	{
		Oid			relid = RelationGetRelid(rel);
		ListCell   *child;
		List	   *children;

		children = find_all_inheritors(relid, lockmode, NULL);


		foreach(child, children)
		{
			Oid			childrelid = lfirst_oid(child);
			Relation	childrel;

			if (childrelid == relid)
				continue;

			childrel = relation_open(childrelid, NoLock);
			CheckTableNotInUse(childrel, "ALTER TABLE");
			ATPrepCmd(wqueue, childrel, cmd, false, true, lockmode);
			relation_close(childrel, NoLock);
		}
	}
}
