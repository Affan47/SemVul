gtu_sr_handle_exchange_rate (GncTreeViewSplitReg *view, gnc_numeric amount, Transaction *trans, Split *split, gboolean force)
{
    GncTreeModelSplitReg *model;
    XferDialog *xfer;
    gboolean rate_split_ok, rate_reg_ok;
    gnc_numeric rate_split, rate_reg, value;
    Account *reg_acc;
    gnc_commodity *xfer_comm = xaccAccountGetCommodity (xaccSplitGetAccount (split));
    gnc_commodity *reg_comm = gnc_tree_view_split_reg_get_reg_commodity (view);
    gnc_commodity *trans_curr = xaccTransGetCurrency (trans);
    gboolean expanded;
    gboolean have_rate = TRUE;

    ENTER("handle_exchange_rate amount %s, trans %p and split %p force %d", gnc_numeric_to_string (amount), trans, split, force);


    model = gnc_tree_view_split_reg_get_model_from_view (view);

    reg_acc = gnc_tree_model_split_reg_get_anchor (model);


    rate_split_ok = xaccTransGetRateForCommodity (trans, xfer_comm, split, &rate_split);
    DEBUG("rate_split_ok %d and xfer_comm %s", rate_split_ok, gnc_commodity_get_fullname (xfer_comm));


    rate_reg_ok = xaccTransGetRateForCommodity (trans, reg_comm, split, &rate_reg);
    DEBUG("rate_reg_ok %d and reg_comm %s", rate_reg_ok, gnc_commodity_get_fullname (reg_comm));


    expanded = gnc_tree_view_split_reg_trans_expanded (view, trans);

    if (gnc_commodity_equal (trans_curr, xfer_comm) && rate_split_ok)
    {
        xaccSplitSetAmount (split, amount);
        xaccSplitSetValue (split, amount);
        return TRUE;
    }

    if (rate_reg_ok && rate_split_ok && !force)
    {
        value = gnc_numeric_div (amount, rate_reg, gnc_commodity_get_fraction (trans_curr), GNC_HOW_DENOM_REDUCE);
        amount = gnc_numeric_mul (value, rate_split, GNC_DENOM_AUTO, GNC_HOW_RND_ROUND);
    }
    else
    {
        if (!rate_split_ok)
            rate_split = gtu_sr_get_rate_from_db (reg_comm, xfer_comm);


        xfer = gnc_xfer_dialog (NULL, NULL);

        gnc_xfer_dialog_is_exchange_dialog (xfer, &rate_split);


        gnc_xfer_dialog_set_description (xfer, xaccTransGetDescription (trans));
        gnc_xfer_dialog_set_memo (xfer, xaccSplitGetMemo (split));


        gnc_xfer_dialog_set_num (xfer, gnc_get_num_action (trans, split));
        gnc_xfer_dialog_set_date (xfer, timespecToTime64 (xaccTransRetDatePostedTS (trans)));

        value = amount;
        if (gnc_xfer_dialog_run_exchange_dialog (xfer, &rate_split, value, reg_acc, trans, xfer_comm, expanded))
        {
            if (!rate_split_ok)
                rate_split = gnc_numeric_create (1, 1);
            have_rate = FALSE;
        }
        else
            have_rate = TRUE;

        amount = gnc_numeric_mul (value, rate_split, GNC_DENOM_AUTO, GNC_HOW_RND_ROUND);
    }
    xaccSplitSetAmount (split, amount);
    xaccSplitSetValue (split, value);

    LEAVE("handle_exchange_rate set split %p amt=%s; and val=%s", split, gnc_numeric_to_string (amount), gnc_numeric_to_string (value));
    return have_rate;
}
