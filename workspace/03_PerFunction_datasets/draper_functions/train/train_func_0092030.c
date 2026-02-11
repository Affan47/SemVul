search_plan_tree(PlanState *node, Oid table_oid)
{
	if (node == NULL)
		return NULL;
	switch (nodeTag(node))
	{


		case T_SeqScanState:
		case T_IndexScanState:
		case T_BitmapHeapScanState:
		case T_TidScanState:
			{
				ScanState  *sstate = (ScanState *) node;

				if (RelationGetRelid(sstate->ss_currentRelation) == table_oid)
					return sstate;
				break;
			}


		case T_AppendState:
			{
				AppendState *astate = (AppendState *) node;
				ScanState  *result = NULL;
				int			i;

				for (i = 0; i < astate->as_nplans; i++)
				{
					ScanState  *elem = search_plan_tree(astate->appendplans[i],
														table_oid);

					if (!elem)
						continue;
					if (result)
						return NULL;
					result = elem;
				}
				return result;
			}


		case T_ResultState:
		case T_LimitState:
			return search_plan_tree(node->lefttree, table_oid);


		case T_SubqueryScanState:
			return search_plan_tree(((SubqueryScanState *) node)->subplan,
									table_oid);

		default:

			break;
	}
	return NULL;
}
