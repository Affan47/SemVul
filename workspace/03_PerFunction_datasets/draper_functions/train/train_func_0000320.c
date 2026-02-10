spin_point_size_changed_value(GtkSpinButton *spinbutton, gpointer user_data)
{
	if(user_data && G_IS_OBJECT(user_data))
	{
		GtkWidget* xyplot = GTK_WIDGET(user_data);
		XYPlotData* data = g_object_get_data(G_OBJECT (spinbutton), "CurentData");

  		g_return_if_fail (GABEDIT_IS_XYPLOT (xyplot));


		if(data)
		{
			data->point_size = gtk_spin_button_get_value(spinbutton);
			xyplot_build_points_data(GABEDIT_XYPLOT(xyplot), data);
		}
		else
		{
			GList *current_node;
			current_node=g_list_first(GABEDIT_XYPLOT(xyplot)->data_list);
			for (; current_node!=NULL; current_node=current_node->next)
			{
				data=(XYPlotData*)current_node->data;
				data->point_size = gtk_spin_button_get_value(spinbutton);
				xyplot_build_points_data(GABEDIT_XYPLOT(xyplot), data);
			}
		}
		gtk_widget_queue_draw(GTK_WIDGET(xyplot));
	}
}
