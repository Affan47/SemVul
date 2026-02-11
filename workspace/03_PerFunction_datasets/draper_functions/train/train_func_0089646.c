gnc_commodity_set_property (GObject         *object,
                            guint            prop_id,
                            const GValue    *value,
                            GParamSpec      *pspec)
{
    gnc_commodity *commodity;

    g_return_if_fail(GNC_IS_COMMODITY(object));

    commodity = GNC_COMMODITY(object);

    switch (prop_id)
    {
    case PROP_NAMESPACE:
        gnc_commodity_set_namespace(commodity, g_value_get_object(value));
        break;
    case PROP_FULL_NAME:
        gnc_commodity_set_fullname(commodity, g_value_get_string(value));
        break;
    case PROP_MNEMONIC:
        gnc_commodity_set_mnemonic(commodity, g_value_get_string(value));
        break;
    case PROP_CUSIP:
        gnc_commodity_set_cusip(commodity, g_value_get_string(value));
        break;
    case PROP_FRACTION:
        gnc_commodity_set_fraction(commodity, g_value_get_int(value));
        break;
    case PROP_QUOTE_FLAG:
        gnc_commodity_set_quote_flag(commodity, g_value_get_boolean(value));
        break;
    case PROP_QUOTE_SOURCE:
        gnc_commodity_set_quote_source(commodity, g_value_get_pointer(value));
        break;
    case PROP_QUOTE_TZ:
        gnc_commodity_set_quote_tz(commodity, g_value_get_string(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
