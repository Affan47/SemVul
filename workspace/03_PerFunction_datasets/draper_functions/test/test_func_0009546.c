osinfo_entity_get_param_value(OsinfoEntity *entity, const gchar *key)
{
    g_return_val_if_fail(OSINFO_IS_ENTITY(entity), NULL);
    g_return_val_if_fail(key != NULL, NULL);

    GList *values;

    if (g_str_equal(key, OSINFO_ENTITY_PROP_ID))
        return entity->priv->id;

    values = g_hash_table_lookup(entity->priv->params, key);

    if (values)
        return values->data;
    return NULL;
}
