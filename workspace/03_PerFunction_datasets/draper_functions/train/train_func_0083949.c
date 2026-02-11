destroy_prev_keyboard_layout_default (GtkWidget *vbox, InputPadGtkWindow *window)
{
    GList *children, *buttons;
    GtkWidget *hbox;
    GtkWidget *table;
    GtkWidget *button;

    children = gtk_container_get_children (GTK_CONTAINER (vbox));
    hbox = GTK_WIDGET (children->data);
    children = gtk_container_get_children (GTK_CONTAINER (hbox));
    while (children) {
        table = GTK_WIDGET (children->data);
        buttons = gtk_container_get_children (GTK_CONTAINER (table));
        while (buttons) {
            button = GTK_WIDGET (buttons->data);
            buttons = buttons->next;
            g_signal_handlers_disconnect_by_func (G_OBJECT (window),
                                                  G_CALLBACK (on_window_keyboard_changed),
                                                  (gpointer) button);
            gtk_widget_hide (button);
            gtk_widget_destroy (button);
        }
        children = children->next;
        gtk_widget_hide (table);
        gtk_widget_destroy (table);
    }
    gtk_widget_hide (hbox);
    gtk_widget_destroy (hbox);
}
