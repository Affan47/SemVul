gnc_popup_entry_init (GncPopupEntry *widget)
{
    GtkWidget *arrow;

    widget->hbox = gtk_hbox_new (FALSE, 0);
    gtk_widget_show (widget->hbox);

    widget->entry = g_object_new (GTK_TYPE_ENTRY, "has_frame", FALSE, NULL);
    GTK_ENTRY (widget->entry)->is_cell_renderer = TRUE;
    gtk_widget_show (widget->entry);

    widget->button = gtk_button_new ();
    gtk_widget_show (widget->button);

    arrow = gtk_arrow_new (GTK_ARROW_DOWN, GTK_SHADOW_OUT);
    gtk_widget_show (arrow);

    gtk_container_add (GTK_CONTAINER (widget->button), arrow);

    gtk_box_pack_start (GTK_BOX (widget->hbox), widget->entry, TRUE, TRUE, 0);
    gtk_box_pack_start (GTK_BOX (widget->hbox), widget->button, FALSE, TRUE, 0);

    gtk_container_add (GTK_CONTAINER (widget), widget->hbox);

    GTK_WIDGET_SET_FLAGS (widget, GTK_CAN_FOCUS);
    gtk_widget_add_events (GTK_WIDGET (widget), GDK_KEY_PRESS_MASK);
    gtk_widget_add_events (GTK_WIDGET (widget), GDK_KEY_RELEASE_MASK);
}
