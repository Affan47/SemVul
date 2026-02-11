status_icon_activate_cb(GtkWidget *widget, gpointer user_data)
{

    gtk_window_deiconify(GTK_WINDOW(hybrid_window));

    if (GTK_WIDGET_VISIBLE(hybrid_window)) {

        if (!gtk_window_is_active(GTK_WINDOW(hybrid_window))) {
            gtk_window_present(GTK_WINDOW(hybrid_window));
            return;
        }
        gtk_widget_hide(hybrid_window);
    } else {
        gtk_widget_show(hybrid_window);
    }
}
