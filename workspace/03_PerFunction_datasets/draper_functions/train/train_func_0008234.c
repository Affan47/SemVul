toggle_action (GtkAction *action)
{
	const gchar *name = gtk_action_get_name (action);
	gboolean enable = gtk_toggle_action_get_active (GTK_TOGGLE_ACTION (action));
	GtkWidget* xyplot = g_object_get_data(G_OBJECT (action), "XYPLOT");
	if(!xyplot) return;
	if(!strcmp(name,"HGridShowMajor"))
		xyplot_enable_grids (GABEDIT_XYPLOT(xyplot), GABEDIT_XYPLOT_HMAJOR_GRID, enable);
	else if(!strcmp(name,"HGridShowMinor"))
		xyplot_enable_grids (GABEDIT_XYPLOT(xyplot), GABEDIT_XYPLOT_HMINOR_GRID, enable);
	else if(!strcmp(name,"VGridShowMajor"))
		xyplot_enable_grids (GABEDIT_XYPLOT(xyplot), GABEDIT_XYPLOT_VMAJOR_GRID, enable);
	else if(!strcmp(name,"VGridShowMinor"))
		xyplot_enable_grids (GABEDIT_XYPLOT(xyplot), GABEDIT_XYPLOT_VMINOR_GRID, enable);
	else if(!strcmp(name,"LegendShowLeft"))
		xyplot_show_left_legends (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"LegendShowRight"))
		xyplot_show_right_legends (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"LegendShowTop"))
		xyplot_show_top_legends (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"LegendShowBottom"))
		xyplot_show_bottom_legends (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"LegendShowRectangle"))
		xyplot_show_rectangle_legends (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"DirectionReflectX"))
		xyplot_reflect_x (GABEDIT_XYPLOT(xyplot), enable);
	else if(!strcmp(name,"DirectionReflectY"))
		xyplot_reflect_y (GABEDIT_XYPLOT(xyplot), enable);
}
