chart_leave(GtkWidget *widget, GdkEventCrossing *event, gpointer user_data)
{
GtkChart *chart = GTK_CHART(user_data);

	if(chart->entries == 0)
		return FALSE;

	chart->active = -1;
	chart->lastactive = -1;

	DB( g_print("\n[gtkchart] leave\n") );
   	DB( g_print(" active is %d\n", chart->active) );

	if (chart->timer_tag)
	{
		g_source_remove (chart->timer_tag);
		chart->timer_tag = 0;
	}

	chart_tooltip_hide(chart);

	gtk_widget_queue_draw(chart->drawarea);

	DB( g_print("----------------\n") );

	return TRUE;
}
