gnc_taxtable_set_property (GObject         *object,
                           guint            prop_id,
                           const GValue          *value,
                           GParamSpec      *pspec)
{
    GncTaxTable *tt;

    g_return_if_fail(GNC_IS_TAXTABLE(object));

    tt = GNC_TAXTABLE(object);
    switch (prop_id)
    {
    case PROP_NAME:
        gncTaxTableSetName(tt, g_value_get_string(value));
        break;
    case PROP_INVISIBLE:
        if (g_value_get_boolean(value))
        {
            gncTaxTableMakeInvisible(tt);
        }
        break;
    case PROP_REFCOUNT:
        gncTaxTableSetRefcount(tt, g_value_get_uint64(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
