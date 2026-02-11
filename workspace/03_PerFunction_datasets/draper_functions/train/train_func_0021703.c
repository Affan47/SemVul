cb_button_clicked(GtkWidget *wid, gTabStrip *data)
{
	if (data->onClose)
		(*data->onClose)(data, data->getRealIndex((GtkWidget *)g_object_get_data(G_OBJECT(wid), "gambas-tab-page")));
}
