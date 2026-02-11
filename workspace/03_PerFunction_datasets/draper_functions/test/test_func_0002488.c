select_row_callback3(GtkWidget *widget,
						 gint row,
						 gint column,
						 GdkEventButton *event,
						 gpointer data)
{
	ManItem * item;
	if(signal_select_row>0) {signal_select_row--;return;}
	item = (ManItem*) gtk_clist_get_row_data(GTK_CLIST(widget),row);
	if(item) item->active_man_page();
}
