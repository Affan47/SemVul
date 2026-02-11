expand_inherited_rtentry(PlannerInfo *root, RangeTblEntry *rte, Index rti)
{
	Query	   *parse = root->parse;
	Oid			parentOID;
	Relation	oldrelation;
	LOCKMODE	lockmode;
	List	   *inhOIDs;
	List	   *appinfos;
	ListCell   *l;


	if (!rte->inh)
		return;

	if (rte->rtekind != RTE_RELATION)
	{
		Assert(rte->rtekind == RTE_SUBQUERY);
		return;
	}

	parentOID = rte->relid;
	if (!has_subclass(parentOID))
	{

		rte->inh = false;
		return;
	}


	inhOIDs = find_all_inheritors(parentOID);


	if (list_length(inhOIDs) < 2)
	{

		rte->inh = false;
		return;
	}


	oldrelation = heap_open(parentOID, NoLock);


	if (rti == parse->resultRelation)
		lockmode = RowExclusiveLock;
	else if (get_rowmark(parse, rti))
		lockmode = RowShareLock;
	else
		lockmode = AccessShareLock;


	appinfos = NIL;
	foreach(l, inhOIDs)
	{
		Oid			childOID = lfirst_oid(l);
		Relation	newrelation;
		RangeTblEntry *childrte;
		Index		childRTindex;
		AppendRelInfo *appinfo;


		if (childOID != parentOID &&
			isOtherTempNamespace(get_rel_namespace(childOID)))
			continue;


		if (childOID != parentOID)
			newrelation = heap_open(childOID, lockmode);
		else
			newrelation = oldrelation;


		childrte = copyObject(rte);
		childrte->relid = childOID;
		childrte->inh = false;
		parse->rtable = lappend(parse->rtable, childrte);
		childRTindex = list_length(parse->rtable);


		appinfo = makeNode(AppendRelInfo);
		appinfo->parent_relid = rti;
		appinfo->child_relid = childRTindex;
		appinfo->parent_reltype = oldrelation->rd_rel->reltype;
		appinfo->child_reltype = newrelation->rd_rel->reltype;
		make_inh_translation_lists(oldrelation, newrelation, childRTindex,
								   &appinfo->col_mappings,
								   &appinfo->translated_vars);
		appinfo->parent_reloid = parentOID;
		appinfos = lappend(appinfos, appinfo);


		if (childOID != parentOID)
			heap_close(newrelation, NoLock);
	}

	heap_close(oldrelation, NoLock);


	if (list_length(appinfos) < 2)
	{

		rte->inh = false;
		return;
	}


	root->append_rel_list = list_concat(root->append_rel_list, appinfos);


	rte->requiredPerms = 0;
}
