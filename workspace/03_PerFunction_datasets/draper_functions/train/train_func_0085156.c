disuse_physical_tlist(Plan *plan, Path *path)
{

	switch (path->pathtype)
	{
		case T_SeqScan:
		case T_IndexScan:
		case T_BitmapHeapScan:
		case T_TidScan:
		case T_SubqueryScan:
		case T_FunctionScan:
		case T_ValuesScan:
			plan->targetlist = build_relation_tlist(path->parent);
			break;
		default:
			break;
	}
}
