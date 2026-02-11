gupnp_didl_lite_descriptor_set_property (GObject      *object,
                                         guint         property_id,
                                         const GValue *value,
                                         GParamSpec   *pspec)
{
        GUPnPDIDLLiteDescriptor *descriptor;

        descriptor = GUPNP_DIDL_LITE_DESCRIPTOR (object);

        switch (property_id) {
        case PROP_XML_NODE:
                descriptor->priv->xml_node = g_value_get_pointer (value);
                break;
        case PROP_XML_DOC:
                descriptor->priv->xml_doc = g_value_dup_object (value);
                break;
        case PROP_ID:
                gupnp_didl_lite_descriptor_set_id
                                        (descriptor,
                                         g_value_get_string (value));
                break;
        case PROP_METADATA_TYPE:
                gupnp_didl_lite_descriptor_set_metadata_type
                                        (descriptor,
                                         g_value_get_string (value));
                break;
        case PROP_NAME_SPACE:
                gupnp_didl_lite_descriptor_set_name_space
                                        (descriptor,
                                         g_value_get_string (value));
                break;
        case PROP_CONTENT:
                gupnp_didl_lite_descriptor_set_content
                                        (descriptor,
                                         g_value_get_string (value));
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}
