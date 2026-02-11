set_foreignscan_references(PlannerInfo *root,
						   ForeignScan *fscan,
						   int rtoffset)
{

	if (fscan->scan.scanrelid > 0)
		fscan->scan.scanrelid += rtoffset;

	if (fscan->fdw_scan_tlist != NIL || fscan->scan.scanrelid == 0)
	{

		indexed_tlist *itlist = build_tlist_index(fscan->fdw_scan_tlist);

		fscan->scan.plan.targetlist = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->scan.plan.targetlist,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		fscan->scan.plan.qual = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->scan.plan.qual,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		fscan->fdw_exprs = (List *)
			fix_upper_expr(root,
						   (Node *) fscan->fdw_exprs,
						   itlist,
						   INDEX_VAR,
						   rtoffset);
		pfree(itlist);

		fscan->fdw_scan_tlist =
			fix_scan_list(root, fscan->fdw_scan_tlist, rtoffset);
	}
	else
	{

		fscan->scan.plan.targetlist =
			fix_scan_list(root, fscan->scan.plan.targetlist, rtoffset);
		fscan->scan.plan.qual =
			fix_scan_list(root, fscan->scan.plan.qual, rtoffset);
		fscan->fdw_exprs =
			fix_scan_list(root, fscan->fdw_exprs, rtoffset);
	}


	if (rtoffset > 0)
	{
		Bitmapset  *tempset = NULL;
		int			x = -1;

		while ((x = bms_next_member(fscan->fs_relids, x)) >= 0)
			tempset = bms_add_member(tempset, x + rtoffset);
		fscan->fs_relids = tempset;
	}
}
