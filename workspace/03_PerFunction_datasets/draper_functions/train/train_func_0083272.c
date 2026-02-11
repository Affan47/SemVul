role_chart_post_add (GogObject *parent, GogObject *chart)
{
	GogGraph *graph = GOG_GRAPH (parent);
	unsigned ypos = 0;
	if (graph->charts != NULL) {

		gboolean *occ = g_alloca (graph->num_rows * sizeof (gboolean));
		GSList *ptr;
		int col, row;
		memset (occ, 0, graph->num_rows * sizeof (gboolean));
		for (ptr = graph->charts; ptr != NULL; ptr = ptr->next)
			if (gog_chart_get_position (GOG_CHART (ptr->data), &col, &row, NULL, NULL) && col == 0 && row < (int) graph->num_rows)
				occ[row] = TRUE;
		while (ypos < graph->num_rows && occ[ypos])
			ypos++;
	}
	graph->charts = g_slist_prepend (graph->charts, chart);
	if (!gog_chart_get_position (GOG_CHART (chart), NULL, NULL, NULL, NULL))

		gog_chart_set_position (GOG_CHART (chart),
			0, ypos, 1, 1);
}
