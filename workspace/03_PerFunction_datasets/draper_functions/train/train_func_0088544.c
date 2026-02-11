ck_session_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
        CkSession *self;

        self = CK_SESSION (object);

        switch (prop_id) {
        case PROP_ACTIVE:
                g_value_set_boolean (value, self->priv->active);
                break;
        case PROP_IS_LOCAL:
                g_value_set_boolean (value, self->priv->is_local);
                break;
        case PROP_ID:
                g_value_set_string (value, self->priv->id);
                break;
        case PROP_COOKIE:
                g_value_set_string (value, self->priv->cookie);
                break;
        case PROP_SESSION_TYPE:
                g_value_set_string (value, self->priv->session_type);
                break;
        case PROP_X11_DISPLAY:
                g_value_set_string (value, self->priv->x11_display);
                break;
        case PROP_X11_DISPLAY_DEVICE:
                g_value_set_string (value, self->priv->x11_display_device);
                break;
        case PROP_DISPLAY_DEVICE:
                g_value_set_string (value, self->priv->display_device);
                break;
        case PROP_LOGIN_SESSION_ID:
                g_value_set_string (value, self->priv->login_session_id);
                break;
        case PROP_UNIX_USER:
                g_value_set_uint (value, self->priv->uid);
                break;
        case PROP_USER:
                g_value_set_uint (value, self->priv->uid);
                break;
        case PROP_REMOTE_HOST_NAME:
                g_value_set_string (value, self->priv->remote_host_name);
                break;
        case PROP_IDLE_HINT:
                g_value_set_boolean (value, self->priv->idle_hint);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
