gwy_graph_label_curve_notify(GwyGraphLabel *label,
                             G_GNUC_UNUSED gint i,
                             GParamSpec *pspec)
{

    if (gwy_strequal(pspec->name, "color")
        || gwy_strequal(pspec->name, "line-style")
        || gwy_strequal(pspec->name, "point-type")) {
        gtk_widget_queue_draw(GTK_WIDGET(label));
        return;
    }

    gwy_graph_label_refresh_all(label);
}
