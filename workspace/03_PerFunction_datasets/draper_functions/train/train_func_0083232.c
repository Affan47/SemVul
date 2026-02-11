gabedit_xyplot_set_data_line_width (GabeditXYPlot *xyplot, gdouble line_width)
{
	g_return_if_fail (xyplot != NULL);
	g_return_if_fail (GABEDIT_IS_XYPLOT (xyplot));

	if(line_width<0) line_width = 0;
	gtk_widget_queue_draw(GTK_WIDGET(xyplot));
	XYPlotData *current_data;
	GList *current_node;

	if (xyplot->data_list ){
		current_node=g_list_first(xyplot->data_list);
		current_data=(XYPlotData*)current_node->data;
		for (; current_node!=NULL; current_node=current_node->next)
		{
        		current_data=(XYPlotData*)current_node->data;
			current_data->line_width = line_width;
		}
	}
	xyplot_free_legends(xyplot);
	xyplot_build_legends(xyplot);
	xyplot_calculate_sizes(xyplot);

	gtk_widget_queue_draw(GTK_WIDGET(xyplot));
}
