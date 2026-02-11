gabedit_xyplot_show_right_legends (GabeditXYPlot *xyplot, gboolean enable)
{
	GtkUIManager *manager = g_object_get_data(G_OBJECT (xyplot), "Manager");
	GtkAction* action = gtk_ui_manager_get_action (manager, "/MenuXYPlot/Render/RenderLegends/LegendShowRight");
	if(action) gtk_toggle_action_set_active(GTK_TOGGLE_ACTION(action),enable);
}
