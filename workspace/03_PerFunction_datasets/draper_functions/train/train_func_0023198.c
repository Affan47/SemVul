ibus_property_serialize (IBusProperty    *prop,
                         GVariantBuilder *builder)
{
    gboolean retval;

    retval = IBUS_SERIALIZABLE_CLASS (ibus_property_parent_class)->serialize ((IBusSerializable *) prop, builder);
    g_return_val_if_fail (retval, FALSE);

    g_return_val_if_fail (IBUS_IS_PROPERTY (prop), FALSE);

    g_variant_builder_add (builder, "s", prop->priv->key);
    g_variant_builder_add (builder, "u", prop->priv->type);
    g_variant_builder_add (builder, "v",
            ibus_serializable_serialize ((IBusSerializable *)prop->priv->label));
    g_variant_builder_add (builder, "s", prop->priv->icon);
    g_variant_builder_add (builder, "v",
            ibus_serializable_serialize ((IBusSerializable *)prop->priv->tooltip));
    g_variant_builder_add (builder, "b", prop->priv->sensitive);
    g_variant_builder_add (builder, "b", prop->priv->visible);
    g_variant_builder_add (builder, "u", prop->priv->state);
    g_variant_builder_add (builder, "v",
            ibus_serializable_serialize ((IBusSerializable *)prop->priv->sub_props));

    g_variant_builder_add (builder, "v",
            ibus_serializable_serialize ((IBusSerializable *)prop->priv->symbol));

    return TRUE;
}
