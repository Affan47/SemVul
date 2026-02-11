gnc_period_select_get_fy_end (GncPeriodSelect *period)
{
    GncPeriodSelectPrivate *priv;
    priv = GNC_PERIOD_SELECT_GET_PRIVATE(period);

    g_return_val_if_fail(period != NULL, NULL);
    g_return_val_if_fail(GNC_IS_PERIOD_SELECT(period), NULL);

    priv = GNC_PERIOD_SELECT_GET_PRIVATE(period);
    if (!priv->fy_end)
        return NULL;
    return g_date_new_dmy(g_date_get_day(priv->fy_end),
                          g_date_get_month(priv->fy_end),
                          G_DATE_BAD_YEAR);
}
