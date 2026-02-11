gnc_lot_get_balance (GNCLot *lot)
{
    LotPrivate* priv;
    GList *node;
    gnc_numeric zero = gnc_numeric_zero();
    gnc_numeric baln = zero;
    if (!lot) return zero;

    priv = GET_PRIVATE(lot);
    if (!priv->splits)
    {
        priv->is_closed = FALSE;
        return zero;
    }


    for (node = priv->splits; node; node = node->next)
    {
        Split *s = node->data;
        gnc_numeric amt = xaccSplitGetAmount (s);
        baln = gnc_numeric_add_fixed (baln, amt);
    }


    if (gnc_numeric_equal (baln, zero))
    {
        priv->is_closed = TRUE;
    }
    else
    {
        priv->is_closed = FALSE;
    }

    return baln;
}
