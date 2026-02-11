_panel_background_reset_widget_style_properties (GtkWidget *widget)
{
        GtkStyleProperties *properties;

        properties = _panel_background_get_widget_style_properties (widget, FALSE);

        if (properties)
                gtk_style_context_remove_provider (gtk_widget_get_style_context (widget),
                                                   GTK_STYLE_PROVIDER (properties));


        g_object_set_data (G_OBJECT (widget), "panel-object-style-props", NULL);
}
