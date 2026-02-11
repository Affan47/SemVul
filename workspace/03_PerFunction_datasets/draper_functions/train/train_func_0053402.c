chart_enter(GtkWidget *widget, GdkEventCrossing *event, gpointer user_data)
{
GtkChart *chart = GTK_CHART(user_data);
gint x, y;

	if(chart->entries == 0)
		return FALSE;

	DB( g_print("++++++++++++++++\n[gtkchart] enter\n") );

	x = event->x;
	y = event->y;

	switch(chart->type)
	{
		case CHART_BAR_TYPE:
			chart->active = barchart_get_active(widget, x, y, chart);
			break;
		case CHART_LINE_TYPE:
			chart->active = linechart_get_active(widget, x, y, chart);
			break;
		case CHART_PIE_TYPE:
			chart->active = piechart_get_active(widget, x, y, chart);
			break;
	}

   	DB( g_print(" active is %d\n", chart->active) );

	return TRUE;
}
