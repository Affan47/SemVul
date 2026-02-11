DefineView(ViewStmt *stmt, const char *queryString)
{
	Query	   *viewParse;
	Oid			viewOid;
	RangeVar   *view;


	viewParse = parse_analyze((Node *) copyObject(stmt->query),
							  queryString, NULL, 0);


	if (!IsA(viewParse, Query) ||
		viewParse->commandType != CMD_SELECT)
		elog(ERROR, "unexpected parse analysis result");


	if (stmt->aliases != NIL)
	{
		ListCell   *alist_item = list_head(stmt->aliases);
		ListCell   *targetList;

		foreach(targetList, viewParse->targetList)
		{
			TargetEntry *te = (TargetEntry *) lfirst(targetList);

			Assert(IsA(te, TargetEntry));

			if (te->resjunk)
				continue;
			te->resname = pstrdup(strVal(lfirst(alist_item)));
			alist_item = lnext(alist_item);
			if (alist_item == NULL)
				break;
		}

		if (alist_item != NULL)
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),
					 errmsg("CREATE VIEW specifies more column "
							"names than columns")));
	}


	view = stmt->view;
	if (!view->istemp && isViewOnTempTable(viewParse))
	{
		view = copyObject(view);
		view->istemp = true;
		ereport(NOTICE,
				(errmsg("view \"%s\" will be a temporary view",
						view->relname)));
	}


	viewOid = DefineVirtualRelation(view, viewParse->targetList,
									stmt->replace);


	CommandCounterIncrement();


	viewParse = UpdateRangeTableOfViewParse(viewOid, viewParse);


	DefineViewRules(viewOid, viewParse, stmt->replace);
}
