accessx_status_applet_layout_box (AccessxStatusApplet *sapplet, GtkWidget *box, GtkWidget *stickyfoo)
{
        AtkObject *atko;

	accessx_status_applet_reparent_widget (sapplet->shift_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->ctrl_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->alt_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->meta_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->hyper_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->super_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->alt_graph_indicator, GTK_CONTAINER (stickyfoo));
	accessx_status_applet_reparent_widget (sapplet->idlefoo, GTK_CONTAINER (box));
	accessx_status_applet_reparent_widget (sapplet->mousefoo, GTK_CONTAINER (box));
	accessx_status_applet_reparent_widget (stickyfoo, GTK_CONTAINER (box));
	accessx_status_applet_reparent_widget (sapplet->slowfoo, GTK_CONTAINER (box));
	accessx_status_applet_reparent_widget (sapplet->bouncefoo, GTK_CONTAINER (box));

	if (sapplet->stickyfoo) {
		gtk_widget_destroy (sapplet->stickyfoo);
	}

	if (sapplet->box) {
		gtk_container_remove (GTK_CONTAINER (sapplet->applet), sapplet->box);
	}

	gtk_container_add (GTK_CONTAINER (sapplet->applet), box);
	sapplet->stickyfoo = stickyfoo;
	sapplet->box = box;

	atko = gtk_widget_get_accessible (sapplet->box);
	atk_object_set_name (atko, _("AccessX Status"));
	atk_object_set_description (atko, _("Shows keyboard status when accessibility features are used."));

	gtk_widget_show (sapplet->box);
	gtk_widget_show (GTK_WIDGET (sapplet->applet));

	if (gtk_widget_get_realized (sapplet->box) &&
            sapplet->initialized)
		accessx_status_applet_update (sapplet, ACCESSX_STATUS_ALL, NULL);
}
