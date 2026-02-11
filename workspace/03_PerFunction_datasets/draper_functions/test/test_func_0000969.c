gnc_lot_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec)
{
    GNCLot* lot;
    LotPrivate* priv;

    g_return_if_fail(GNC_IS_LOT(object));

    lot = GNC_LOT(object);
    priv = GET_PRIVATE(lot);
    switch (prop_id)
    {
    case PROP_IS_CLOSED:
        g_value_set_int(value, priv->is_closed);
        break;
    case PROP_MARKER:
        g_value_set_int(value, priv->marker);
        break;
    }
}
