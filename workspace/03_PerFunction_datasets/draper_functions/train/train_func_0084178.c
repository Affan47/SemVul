mb_table_toggled_event(GtkWidget *widget, Application *app)
{
	if(GTK_TOGGLE_BUTTON(widget)->active)
		app->table_choice = 1;
		refresh_table(app->drawing_area, app);
}
