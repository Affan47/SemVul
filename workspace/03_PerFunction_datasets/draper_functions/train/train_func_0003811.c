ibus_serializable_serialize (IBusSerializable *object)
{
    g_return_val_if_fail (IBUS_IS_SERIALIZABLE (object), FALSE);
    gboolean retval;

    GVariantBuilder builder;
    g_variant_builder_init (&builder, G_VARIANT_TYPE_TUPLE);

    g_variant_builder_add (&builder, "s", g_type_name (G_OBJECT_TYPE (object)));
    retval = IBUS_SERIALIZABLE_GET_CLASS (object)->serialize (object, &builder);
    g_assert (retval);

    return g_variant_builder_end (&builder);
}
