qof_instance_get_property (GObject         *object,
                           guint            prop_id,
                           GValue          *value,
                           GParamSpec      *pspec)
{
    QofInstance *inst;
    QofInstancePrivate *priv;

    g_return_if_fail(QOF_IS_INSTANCE(object));

    inst = QOF_INSTANCE(object);
    priv = GET_PRIVATE(inst);

    switch (prop_id)
    {
    case PROP_GUID:
        g_value_set_boxed(value, &priv->guid);
        break;
    case PROP_COLLECTION:
        g_value_set_pointer(value, priv->collection);
        break;
    case PROP_BOOK:
        g_value_take_object(value, priv->book);
        break;
    case PROP_KVP_DATA:
        g_value_set_pointer(value, inst->kvp_data);
        break;
    case PROP_LAST_UPDATE:
        g_value_set_pointer(value, &priv->last_update);
        break;
    case PROP_EDITLEVEL:
        g_value_set_int(value, priv->editlevel);
        break;
    case PROP_DESTROYING:
        g_value_set_boolean(value, priv->do_free);
        break;
    case PROP_DIRTY:
        g_value_set_boolean(value, qof_instance_get_dirty(inst));
        break;
    case PROP_INFANT:
        g_value_set_boolean(value, priv->infant);
        break;
    case PROP_VERSION:
        g_value_set_int(value, priv->version);
        break;
    case PROP_VERSION_CHECK:
        g_value_set_uint(value, priv->version_check);
        break;
    case PROP_IDATA:
        g_value_set_uint(value, priv->idata);
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
