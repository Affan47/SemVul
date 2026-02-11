ATAddCheckConstraint(List **wqueue, AlteredTableInfo *tab, Relation rel,
					 Constraint *constr, bool recurse, bool recursing)
{
	List	   *newcons;
	ListCell   *lcon;
	List	   *children;
	ListCell   *child;


	if (recursing)
		ATSimplePermissions(rel, false);


	newcons = AddRelationNewConstraints(rel, NIL,
										list_make1(copyObject(constr)),
										recursing, !recursing);


	foreach(lcon, newcons)
	{
		CookedConstraint *ccon = (CookedConstraint *) lfirst(lcon);
		NewConstraint *newcon;

		newcon = (NewConstraint *) palloc0(sizeof(NewConstraint));
		newcon->name = ccon->name;
		newcon->contype = ccon->contype;

		newcon->qual = (Node *) make_ands_implicit((Expr *) ccon->expr);

		tab->constraints = lappend(tab->constraints, newcon);


		if (constr->conname == NULL)
			constr->conname = ccon->name;
	}


	Assert(constr->conname != NULL);


	CommandCounterIncrement();


	if (newcons == NIL)
		return;


	children = find_inheritance_children(RelationGetRelid(rel),
										 AccessExclusiveLock);


	if (children && !recurse)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TABLE_DEFINITION),
				 errmsg("constraint must be added to child tables too")));

	foreach(child, children)
	{
		Oid			childrelid = lfirst_oid(child);
		Relation	childrel;
		AlteredTableInfo *childtab;


		childrel = heap_open(childrelid, NoLock);
		CheckTableNotInUse(childrel, "ALTER TABLE");


		childtab = ATGetQueueEntry(wqueue, childrel);


		ATAddCheckConstraint(wqueue, childtab, childrel,
							 constr, recurse, true);

		heap_close(childrel, NoLock);
	}
}
