panel_widget_size_request(GtkWidget *widget, GtkRequisition *requisition)
{
	PanelWidget *panel;
	GList *list;
	gboolean dont_fill;

	g_return_if_fail(PANEL_IS_WIDGET(widget));
	g_return_if_fail(requisition!=NULL);

	panel = PANEL_WIDGET(widget);

	if(panel->orient == GTK_ORIENTATION_HORIZONTAL) {
		requisition->width = 0;
		requisition->height = panel->sz;
	} else {
		requisition->height = 0;
		requisition->width = panel->sz;
	}

	for(list = panel->applet_list; list!=NULL; list = g_list_next(list)) {
		AppletData *ad = list->data;
                GtkRequisition child_req;

                gtk_widget_get_preferred_size (ad->applet, &child_req, NULL);

		if (panel->orient == GTK_ORIENTATION_HORIZONTAL) {
			if (requisition->height < child_req.height &&
			    !ad->size_constrained)
				requisition->height = child_req.height;

			if (panel->packed &&
			    !(ad->expand_major && ad->size_hints))
				requisition->width += child_req.width;
		} else {
			if (requisition->width < child_req.width &&
			    !ad->size_constrained)
				requisition->width = child_req.width;

			if (panel->packed &&
			    !(ad->expand_major && ad->size_hints))
				requisition->height += child_req.height;
		}
	}

	dont_fill = panel->packed && panel->nb_applets_size_hints != 0;

	if (panel->orient == GTK_ORIENTATION_HORIZONTAL) {
		if (requisition->width < 12 && !dont_fill)
			requisition->width = 12;
		if (requisition->height < 12)
			requisition->height = 12;
	} else {
		if (requisition->width < 12)
			requisition->width = 12;
		if (requisition->height < 12 && !dont_fill)
			requisition->height = 12;
	}
}
