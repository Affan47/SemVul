gog_chart_foreach_elem (GogChart *chart, gboolean only_visible,
			GogEnumFunc handler, gpointer data)
{
	GSList *ptr;

	g_return_if_fail (GOG_IS_CHART (chart));
	g_return_if_fail (chart->cardinality_valid);

	for (ptr = chart->plots ; ptr != NULL ; ptr = ptr->next)
		gog_plot_foreach_elem (ptr->data, only_visible, handler, data);
}
