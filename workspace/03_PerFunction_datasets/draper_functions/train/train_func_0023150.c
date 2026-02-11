ATTypedTableRecursion(List **wqueue, Relation rel, AlterTableCmd *cmd,
		      LOCKMODE lockmode)
{
  ListCell   *child;
  List	   *children;

  Assert(rel->rd_rel->relkind == RELKIND_COMPOSITE_TYPE);

  children = find_typed_table_dependencies(rel->rd_rel->reltype,
					   RelationGetRelationName(rel),
					   cmd->behavior);

  foreach(child, children)
    {
      Oid			childrelid = lfirst_oid(child);
      Relation	childrel;

      childrel = relation_open(childrelid, lockmode);
      CheckTableNotInUse(childrel, "ALTER TABLE");
      ATPrepCmd(wqueue, childrel, cmd, true, true, lockmode);
      relation_close(childrel, NoLock);
    }
}
