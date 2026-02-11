glade_popup_menuitem_ph_packing_activated (GtkMenuItem *item, const gchar *action_path)
{
	GladePlaceholder *ph;
	GladeWidget *parent;

	if ((ph = g_object_get_data (G_OBJECT (item), "gwa-data")))
	{
		parent = glade_placeholder_get_parent (ph);
		glade_widget_adaptor_child_action_activate (parent->adaptor,
							    parent->object,
							    G_OBJECT (ph),
							    action_path);
	}
}
