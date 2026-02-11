get_combobox_appearance_name (GtkWidget *combobox)
{
    const gchar *widget_name;

    g_return_val_if_fail (combobox != NULL && GTK_IS_WIDGET (combobox), NULL);

    widget_name = get_widget_name (combobox);
    if (widget_name == NULL) {
        return NULL;
    }
    return g_strdup (widget_name);
}
