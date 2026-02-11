main_window_add_status_icon(GtkWidget * icon)
{
    GtkWidget *hbox = GTK_WIDGET(gtk_builder_get_object(pl3_xml, "status-icon-hbox"));
    g_return_if_fail(icon != NULL);
    gtk_box_pack_start(GTK_BOX(hbox), icon, FALSE, TRUE, 0);
}
