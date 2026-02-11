gsm_autostart_app_get_property (GObject    *object,
                                guint       prop_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
        GsmAutostartApp *self;

        self = GSM_AUTOSTART_APP (object);

        switch (prop_id) {
        case PROP_DESKTOP_FILENAME:
                if (self->priv->app_info != NULL) {
                        g_value_set_string (value, g_desktop_app_info_get_filename (self->priv->app_info));
                } else {
                        g_value_set_string (value, NULL);
                }
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
