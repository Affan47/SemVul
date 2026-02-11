sort_project_dependancies (GObject *a, GObject *b)
{
	GladeWidget *ga, *gb;

	ga = glade_widget_get_from_gobject (a);
	gb = glade_widget_get_from_gobject (b);

	if (glade_widget_adaptor_depends (ga->adaptor, ga, gb))
		return 1;
	else if (glade_widget_adaptor_depends (gb->adaptor, gb, ga))
		return -1;
	else
		return strcmp (ga->name, gb->name);
}
