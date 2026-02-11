get_initial_counters (GitgDiffView *view, Region *region, guint line, guint counters[2])
{
	guint i;

	counters[0] = counters[1] = 0;

	for (i = region->line + 1; i < line; ++i)
	{
		if (draw_old (view, i))
			++counters[0];

		if (draw_new (view, i))
			++counters[1];
	}
}
