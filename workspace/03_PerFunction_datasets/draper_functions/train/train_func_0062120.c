vnc_base_framebuffer_get_property(GObject *object,
                                              guint prop_id,
                                              GValue *value,
                                              GParamSpec *pspec)
{
    VncBaseFramebuffer *framebuffer = VNC_BASE_FRAMEBUFFER(object);
    VncBaseFramebufferPrivate *priv = framebuffer->priv;

    switch (prop_id) {
    case PROP_BUFFER:
        g_value_set_pointer(value, priv->buffer);
        break;

    case PROP_WIDTH:
        g_value_set_int(value, priv->width);
        break;

    case PROP_HEIGHT:
        g_value_set_int(value, priv->height);
        break;

    case PROP_ROWSTRIDE:
        g_value_set_int(value, priv->rowstride);
        break;

    case PROP_LOCAL_FORMAT:
        g_value_set_boxed(value, priv->localFormat);
        break;

    case PROP_REMOTE_FORMAT:
        g_value_set_boxed(value, priv->remoteFormat);
        break;

    case PROP_COLOR_MAP:
        g_value_set_boxed(value, priv->colorMap);
        break;

    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    }
}
