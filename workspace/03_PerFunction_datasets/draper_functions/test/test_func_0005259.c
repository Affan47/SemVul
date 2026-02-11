gnc_print_check_set_sensitive (GtkWidget *widget, gpointer data)
{
    gboolean sensitive;
    if (GTK_IS_LABEL(widget) || GTK_IS_SEPARATOR(widget))
        return;
    sensitive = GPOINTER_TO_INT(data);
    gtk_widget_set_sensitive(widget, sensitive);
}
