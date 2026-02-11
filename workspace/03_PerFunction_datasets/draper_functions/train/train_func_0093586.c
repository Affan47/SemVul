empty_cond_settings_list (GsdXSettingsGtk *gtk)
{
        if (gtk->priv->cond_settings == NULL)
                return;


        g_list_foreach (gtk->priv->cond_settings, (GFunc) g_object_unref, NULL);
        g_list_free (gtk->priv->cond_settings);
        gtk->priv->cond_settings = NULL;
}
