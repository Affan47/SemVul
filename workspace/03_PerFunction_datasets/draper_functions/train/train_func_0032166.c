cal_no_margin_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    GtkWidget *cal = GTK_WIDGET(user_data);
    GtkBuilder *cal_xml = _get_calendar_xml(cal);
    gboolean sens = !gtk_toggle_button_get_active(togglebutton);

    if ((GtkWidget *) togglebutton == gtkpod_builder_xml_get_widget(cal_xml, "no_lower_margin")) {
        gtk_widget_set_sensitive(gtkpod_builder_xml_get_widget(cal_xml, "lower_cal_box"), sens);
    }
    if ((GtkWidget *) togglebutton == gtkpod_builder_xml_get_widget(cal_xml, "no_upper_margin")) {
        gtk_widget_set_sensitive(gtkpod_builder_xml_get_widget(cal_xml, "upper_cal_box"), sens);
    }
}
