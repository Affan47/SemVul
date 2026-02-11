compare_windows(SortType type, WinData *a, WinData *b)
{
	int wa, wb;

	if (type == SortId)
	{
		return a->app_id - b->app_id;
	}
	else if (type == SortName)
	{
		return strcasecmp(
			(a->display_string)? a->display_string:"",
			(b->display_string)? b->display_string:"");
	}
	else if (type == SortNameCase)
	{
		return strcmp((a->display_string)? a->display_string:"",
			       (b->display_string)? b->display_string:"");
	}
	else if (type == SortWeighted)
	{
		wa = compute_weight(a);
		wb = compute_weight(b);
		if (wa != wb)
		{
			return wa - wb;
		}
		return strcmp((a->display_string)? a->display_string:"",
			      (b->display_string)? b->display_string:"");
	}
	else
	{
		ConsoleMessage("Internal error in compare_windows\n");
		return 0;
	}
}
