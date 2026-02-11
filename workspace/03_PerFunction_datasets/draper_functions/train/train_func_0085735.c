updata_widget_show(int flag)
{
	long k,k2;

	k = (long)context->get_value("searching_mode");
	k2 = (long)context->get_value("show_status_bar");

	if(k2&(1<<k))
		gtk_widget_show(hbox_status);
	else
		gtk_widget_hide(hbox_status);
	gtk_widget_hide(!k?keyword_search_vbox:index_search_vbox);
	gtk_widget_show(k?keyword_search_vbox:index_search_vbox);
	if(k2 & (1<<k)) gtk_widget_show (hbox_status);
}
