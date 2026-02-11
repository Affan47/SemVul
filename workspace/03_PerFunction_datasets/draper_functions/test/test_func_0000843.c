pan_item_text_layout(PanItem *pi, GtkWidget *widget)
{
	PangoLayout *layout;

	layout = gtk_widget_create_pango_layout(widget, NULL);

	if (pi->text_attr & PAN_TEXT_ATTR_MARKUP)
		{
		pango_layout_set_markup(layout, pi->text, -1);
		return layout;
		}

	if (pi->text_attr & PAN_TEXT_ATTR_BOLD ||
	    pi->text_attr & PAN_TEXT_ATTR_HEADING)
		{
		PangoAttrList *pal;
		PangoAttribute *pa;

		pal = pango_attr_list_new();
		if (pi->text_attr & PAN_TEXT_ATTR_BOLD)
			{
			pa = pango_attr_weight_new(PANGO_WEIGHT_BOLD);
			pa->start_index = 0;
			pa->end_index = G_MAXINT;
			pango_attr_list_insert(pal, pa);
			}
		if (pi->text_attr & PAN_TEXT_ATTR_HEADING)
			{
			pa = pango_attr_scale_new(PANGO_SCALE_LARGE);
			pa->start_index = 0;
			pa->end_index = G_MAXINT;
			pango_attr_list_insert(pal, pa);
			}
		pango_layout_set_attributes(layout, pal);
		pango_attr_list_unref(pal);
		}

	pango_layout_set_text(layout, pi->text, -1);
	return layout;
}
