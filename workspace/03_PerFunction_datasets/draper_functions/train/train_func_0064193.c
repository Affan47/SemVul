show_handlebox_status(gboolean show)
{
	if(!handleboxStatus) return;
	gtk_widget_hide(handleboxStatus);
	if(show) gtk_widget_show(handleboxStatus);
}
