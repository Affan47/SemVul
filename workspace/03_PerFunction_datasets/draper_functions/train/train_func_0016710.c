resize(int w, int h)
{
	gControl::resize(w,h);

	if (entry)
		gtk_widget_set_size_request(entry, width(), height());
}
