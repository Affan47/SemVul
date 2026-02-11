gnm_sog_foreach_dep (SheetObject *so,
		     SheetObjectForeachDepFunc func,
		     gpointer user)
{
	SheetObjectGraph *sog = SHEET_OBJECT_GRAPH (so);
	GSList *ptr = gog_graph_get_data (sog->graph);
	for (; ptr != NULL ; ptr = ptr->next)
		sog_data_foreach_dep (so, ptr->data, func, user);
}
