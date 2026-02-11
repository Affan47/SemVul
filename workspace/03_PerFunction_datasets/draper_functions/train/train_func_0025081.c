build_index_pathkeys(PlannerInfo *root,
					 IndexOptInfo *index,
					 ScanDirection scandir,
					 bool canonical)
{
	List	   *retval = NIL;
	int		   *indexkeys = index->indexkeys;
	Oid		   *ordering = index->ordering;
	ListCell   *indexprs_item = list_head(index->indexprs);

	while (*ordering != InvalidOid)
	{
		PathKeyItem *item;
		Oid			sortop;
		Node	   *indexkey;
		List	   *cpathkey;

		sortop = *ordering;
		if (ScanDirectionIsBackward(scandir))
		{
			sortop = get_commutator(sortop);
			if (sortop == InvalidOid)
				break;
		}

		if (*indexkeys != 0)
		{

			indexkey = (Node *) find_indexkey_var(root, index->rel,
												  *indexkeys);
		}
		else
		{

			if (indexprs_item == NULL)
				elog(ERROR, "wrong number of index expressions");
			indexkey = (Node *) lfirst(indexprs_item);
			indexprs_item = lnext(indexprs_item);
		}


		item = makePathKeyItem(indexkey, sortop, true);
		cpathkey = make_canonical_pathkey(root, item);


		if (canonical)
			retval = list_append_unique_ptr(retval, cpathkey);
		else
			retval = lappend(retval, cpathkey);

		indexkeys++;
		ordering++;
	}

	return retval;
}
