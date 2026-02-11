cc_background_item_get_property (GObject    *object,
                                 guint       prop_id,
                                 GValue     *value,
                                 GParamSpec *pspec)
{
        CcBackgroundItem *self;

        self = CC_BACKGROUND_ITEM (object);

        switch (prop_id) {
        case PROP_NAME:
                g_value_set_string (value, self->priv->name);
                break;
	case PROP_URI:
                g_value_set_string (value, self->priv->uri);
                break;
        case PROP_PLACEMENT:
                g_value_set_enum (value, self->priv->placement);
                break;
        case PROP_SHADING:
                g_value_set_enum (value, self->priv->shading);
                break;
        case PROP_PRIMARY_COLOR:
                g_value_set_string (value, self->priv->primary_color);
                break;
        case PROP_SECONDARY_COLOR:
                g_value_set_string (value, self->priv->secondary_color);
                break;
        case PROP_IS_DELETED:
                g_value_set_boolean (value, self->priv->is_deleted);
                break;
	case PROP_SOURCE_URL:
		g_value_set_string (value, self->priv->source_url);
		break;
	case PROP_SOURCE_XML:
		g_value_set_string (value, self->priv->source_xml);
		break;
	case PROP_FLAGS:
		g_value_set_flags (value, self->priv->flags);
		break;
	case PROP_SIZE:
		g_value_set_string (value, self->priv->size);
		break;
	case PROP_NEEDS_DOWNLOAD:
		g_value_set_boolean (value, self->priv->needs_download);
		break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
