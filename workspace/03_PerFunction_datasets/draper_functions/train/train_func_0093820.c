xaccSplitSetBaseValue (Split *s, gnc_numeric value,
                       const gnc_commodity * base_currency)
{
    const gnc_commodity *currency;
    const gnc_commodity *commodity;

    if (!s) return;
    xaccTransBeginEdit (s->parent);

    if (!s->acc)
    {
        PERR ("split must have a parent account");
        return;
    }

    currency = xaccTransGetCurrency (s->parent);
    commodity = xaccAccountGetCommodity (s->acc);


    if (gnc_commodity_equiv(currency, base_currency))
    {
        if (gnc_commodity_equiv(commodity, base_currency))
        {
            s->amount = gnc_numeric_convert(value,
                                            get_commodity_denom(s),
                                            GNC_HOW_RND_ROUND_HALF_UP);
        }
        s->value = gnc_numeric_convert(value,
                                       get_currency_denom(s),
                                       GNC_HOW_RND_ROUND_HALF_UP);
    }
    else if (gnc_commodity_equiv(commodity, base_currency))
    {
        s->amount = gnc_numeric_convert(value, get_commodity_denom(s),
                                        GNC_HOW_RND_ROUND_HALF_UP);
    }
    else
    {
        PERR ("inappropriate base currency %s "
              "given split currency=%s and commodity=%s\n",
              gnc_commodity_get_printname(base_currency),
              gnc_commodity_get_printname(currency),
              gnc_commodity_get_printname(commodity));
        return;
    }

    SET_GAINS_A_VDIRTY(s);
    mark_split (s);
    qof_instance_set_dirty(QOF_INSTANCE(s));
    xaccTransCommitEdit(s->parent);
}
