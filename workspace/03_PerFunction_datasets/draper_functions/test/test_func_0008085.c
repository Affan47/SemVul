gdm_launch_environment_get_property (GObject    *object,
                                     guint       prop_id,
                                     GValue     *value,
                                     GParamSpec *pspec)
{
        GdmLaunchEnvironment *self;

        self = GDM_LAUNCH_ENVIRONMENT (object);

        switch (prop_id) {
        case PROP_VERIFICATION_MODE:
                g_value_set_enum (value, self->priv->verification_mode);
                break;
        case PROP_X11_DISPLAY_NAME:
                g_value_set_string (value, self->priv->x11_display_name);
                break;
        case PROP_X11_DISPLAY_SEAT_ID:
                g_value_set_string (value, self->priv->x11_display_seat_id);
                break;
        case PROP_X11_DISPLAY_HOSTNAME:
                g_value_set_string (value, self->priv->x11_display_hostname);
                break;
        case PROP_X11_DISPLAY_DEVICE:
                g_value_set_string (value, self->priv->x11_display_device);
                break;
        case PROP_X11_DISPLAY_IS_LOCAL:
                g_value_set_boolean (value, self->priv->x11_display_is_local);
                break;
        case PROP_X11_AUTHORITY_FILE:
                g_value_set_string (value, self->priv->x11_authority_file);
                break;
        case PROP_USER_NAME:
                g_value_set_string (value, self->priv->user_name);
                break;
        case PROP_RUNTIME_DIR:
                g_value_set_string (value, self->priv->runtime_dir);
                break;
        case PROP_DBUS_SESSION_BUS_ADDRESS:
                g_value_set_string (value, self->priv->dbus_session_bus_address);
                break;
        case PROP_COMMAND:
                g_value_set_string (value, self->priv->command);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
