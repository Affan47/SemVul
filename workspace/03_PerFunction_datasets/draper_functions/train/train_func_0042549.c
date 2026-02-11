gnc_split_register_save_amount_values (SRSaveData *sd, SplitRegister *reg)
{
    Account *acc;
    gnc_numeric new_amount, convrate, amtconv, value;
    gnc_commodity *curr, *reg_com, *xfer_com;
    Account *xfer_acc;

    new_amount = gnc_split_register_debcred_cell_value (reg);
    acc = gnc_split_register_get_default_account (reg);

    xfer_acc = xaccSplitGetAccount (sd->split);
    xfer_com = xaccAccountGetCommodity (xfer_acc);
    reg_com = xaccAccountGetCommodity (acc);
    curr = xaccTransGetCurrency (sd->trans);


    amtconv = convrate = gnc_split_register_get_rate_cell (reg, RATE_CELL);
    if (acc && gnc_split_register_needs_conv_rate (reg, sd->trans, acc))
    {


        if (sd->reg_expanded && ! gnc_commodity_equal (reg_com, xfer_com))
            amtconv = xaccTransGetAccountConvRate(sd->trans, acc);
    }

    if (xaccTransUseTradingAccounts (sd->trans))
    {


        gboolean is_amount;
        if (reg->type == STOCK_REGISTER ||
                reg->type == CURRENCY_REGISTER ||
                reg->type == PORTFOLIO_LEDGER)
        {
            if (xaccAccountIsPriced(xfer_acc) ||
                    !gnc_commodity_is_iso(xaccAccountGetCommodity(xfer_acc)))
                is_amount = FALSE;
            else
                is_amount = TRUE;
        }
        else
        {
            is_amount = TRUE;
        }

        if (is_amount)
        {
            xaccSplitSetAmount(sd->split, new_amount);
            if (gnc_split_register_split_needs_amount (reg, sd->split))
            {
                value = gnc_numeric_div(new_amount, amtconv,
                                        gnc_commodity_get_fraction(curr),
                                        GNC_HOW_RND_ROUND_HALF_UP);
                xaccSplitSetValue(sd->split, value);
            }
            else
                xaccSplitSetValue(sd->split, new_amount);
        }
        else
        {
            xaccSplitSetValue(sd->split, new_amount);
        }

        return;
    }


    if (acc && gnc_split_register_needs_conv_rate (reg, sd->trans, acc))
    {


        value = gnc_numeric_div (new_amount, amtconv,
                                 gnc_commodity_get_fraction (curr),
                                 GNC_HOW_RND_ROUND_HALF_UP);
        xaccSplitSetValue (sd->split, value);
    }
    else
        xaccSplitSetValue (sd->split, new_amount);


    value = xaccSplitGetValue (sd->split);

    if (gnc_split_register_split_needs_amount (reg, sd->split))
    {
        acc = xaccSplitGetAccount (sd->split);
        new_amount = gnc_numeric_mul (value, convrate,
                                      xaccAccountGetCommoditySCU (acc),
                                      GNC_HOW_RND_ROUND_HALF_UP);
        xaccSplitSetAmount (sd->split, new_amount);
    }
}
