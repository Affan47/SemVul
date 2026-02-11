gva_ui_get_managed_widget (const gchar *widget_path)
{
        GtkWidget *widget;

        g_return_val_if_fail (widget_path != NULL, NULL);

        if (G_UNLIKELY (!initialized))
                ui_init ();

        widget = gtk_ui_manager_get_widget (manager, widget_path);
        g_assert (widget != NULL);
        return widget;
}
