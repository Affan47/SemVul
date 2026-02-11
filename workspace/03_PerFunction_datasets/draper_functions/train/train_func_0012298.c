set_gtk_im_module (GsdKeyboardManager *manager,
                   GVariant           *sources)
{
        GsdKeyboardManagerPrivate *priv = manager->priv;
        const gchar *new_module;
        gchar *current_module;

        if (!sources || need_ibus (sources))
                new_module = GTK_IM_MODULE_IBUS;
        else
                new_module = GTK_IM_MODULE_SIMPLE;

        current_module = g_settings_get_string (priv->interface_settings,
                                                KEY_GTK_IM_MODULE);
        if (!g_str_equal (current_module, new_module))
                g_settings_set_string (priv->interface_settings,
                                       KEY_GTK_IM_MODULE,
                                       new_module);
        g_free (current_module);
}
