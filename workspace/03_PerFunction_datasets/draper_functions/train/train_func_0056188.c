rsvg_handle_get_property (GObject * instance, guint prop_id, GValue * value, GParamSpec * pspec)
{
    RsvgHandle *self = RSVG_HANDLE (instance);
    RsvgDimensionData dim;

    switch (prop_id) {
    case PROP_FLAGS:
        g_value_set_flags (value, self->priv->flags);
        break;
    case PROP_DPI_X:
        g_value_set_double (value, self->priv->dpi_x);
        break;
    case PROP_DPI_Y:
        g_value_set_double (value, self->priv->dpi_y);
        break;
    case PROP_BASE_URI:
        g_value_set_string (value, rsvg_handle_get_base_uri (self));
        break;
    case PROP_WIDTH:
        rsvg_handle_get_dimensions (self, &dim);
        g_value_set_int (value, dim.width);
        break;
    case PROP_HEIGHT:
        rsvg_handle_get_dimensions (self, &dim);
        g_value_set_int (value, dim.height);
        break;
    case PROP_EM:
        rsvg_handle_get_dimensions (self, &dim);
        g_value_set_double (value, dim.em);
        break;
    case PROP_EX:
        rsvg_handle_get_dimensions (self, &dim);
        g_value_set_double (value, dim.ex);
        break;
    case PROP_TITLE:
        g_value_set_string (value, rsvg_handle_get_title (self));
        break;
    case PROP_DESC:
        g_value_set_string (value, rsvg_handle_get_desc (self));
        break;
    case PROP_METADATA:
        g_value_set_string (value, rsvg_handle_get_metadata (self));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (instance, prop_id, pspec);
    }
}
