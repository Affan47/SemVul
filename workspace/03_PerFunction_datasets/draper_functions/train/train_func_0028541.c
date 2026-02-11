ibus_engine_desc_deserialize (IBusEngineDesc *desc,
                              GVariant       *variant)
{
    gint retval;

    retval = IBUS_SERIALIZABLE_CLASS (ibus_engine_desc_parent_class)->deserialize ((IBusSerializable *)desc, variant);
    g_return_val_if_fail (retval, 0);


    g_variant_get_child (variant, retval++, "s", &desc->priv->name);
    g_variant_get_child (variant, retval++, "s", &desc->priv->longname);
    g_variant_get_child (variant, retval++, "s", &desc->priv->description);
    g_variant_get_child (variant, retval++, "s", &desc->priv->language);
    g_variant_get_child (variant, retval++, "s", &desc->priv->license);
    g_variant_get_child (variant, retval++, "s", &desc->priv->author);
    g_variant_get_child (variant, retval++, "s", &desc->priv->icon);
    g_variant_get_child (variant, retval++, "s", &desc->priv->layout);
    g_variant_get_child (variant, retval++, "u", &desc->priv->rank);

    g_variant_get_child (variant, retval++, "s", &desc->priv->hotkeys);
    g_variant_get_child (variant, retval++, "s", &desc->priv->symbol);
    g_variant_get_child (variant, retval++, "s", &desc->priv->setup);
    if (g_variant_n_children (variant) < retval + 2)
        return retval;
    g_variant_get_child (variant, retval++, "s", &desc->priv->layout_variant);
    g_variant_get_child (variant, retval++, "s", &desc->priv->layout_option);
    if (g_variant_n_children (variant) < retval + 1)
        return retval;
    g_variant_get_child (variant, retval++, "s", &desc->priv->version);
    if (g_variant_n_children (variant) < retval + 1)
        return retval;
    g_variant_get_child (variant, retval++, "s", &desc->priv->textdomain);

    return retval;
}
