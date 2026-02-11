ibus_xkb_config_registry_destroy (IBusXKBConfigRegistry *xkb_config)
{
    IBusXKBConfigRegistryPrivate *priv;

    g_return_if_fail (xkb_config != NULL);

    priv = IBUS_XKB_CONFIG_REGISTRY_GET_PRIVATE (xkb_config);

    g_hash_table_destroy (priv->layout_list);
    priv->layout_list = NULL;
    g_hash_table_destroy (priv->layout_lang);
    priv->layout_lang= NULL;
    g_hash_table_destroy (priv->layout_desc);
    priv->layout_desc= NULL;
    g_hash_table_destroy (priv->variant_desc);
    priv->variant_desc = NULL;

    IBUS_OBJECT_CLASS(ibus_xkb_config_registry_parent_class)->destroy (IBUS_OBJECT (xkb_config));
}
