goa_editable_label_set_property (GObject      *object,
                                guint         prop_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
        GoaEditableLabel *e = GOA_EDITABLE_LABEL (object);

        switch (prop_id) {
        case PROP_TEXT:
                goa_editable_label_set_text (e, g_value_get_string (value));
                break;
        case PROP_EDITABLE:
                goa_editable_label_set_editable (e, g_value_get_boolean (value));
                break;
        case PROP_WEIGHT:
                goa_editable_label_set_weight (e, g_value_get_int (value));
                break;
        case PROP_WEIGHT_SET:
                e->priv->weight_set = g_value_get_boolean (value);
                break;
        case PROP_SCALE:
                goa_editable_label_set_scale (e, g_value_get_double (value));
                break;
        case PROP_SCALE_SET:
                e->priv->scale_set = g_value_get_boolean (value);
                break;
        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
                break;
        }
}
