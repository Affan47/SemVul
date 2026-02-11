gtu_sr_needs_exchange_rate (GncTreeViewSplitReg *view, Transaction *trans, Split *split)
{
    gnc_commodity *split_com, *txn_curr, *reg_com;

    ENTER("gtu_sr_needs_exchange_rate - trans %p and split %p", trans, split);

    txn_curr = xaccTransGetCurrency (trans);
    split_com = xaccAccountGetCommodity (xaccSplitGetAccount (split));
    if (split_com && txn_curr && !gnc_commodity_equiv (split_com, txn_curr))
    {
        LEAVE("gtu_sr_needs_exchange_rate split_com to txn_curr return TRUE");
        return TRUE;
    }

    reg_com = gnc_tree_view_split_reg_get_reg_commodity (view);
    if (split_com && reg_com && !gnc_commodity_equiv (split_com, reg_com))
    {
        LEAVE("gtu_sr_needs_exchange_rate split_com and reg_com return TRUE");
        return TRUE;
    }
    LEAVE("No Exchange rate needed");
    return FALSE;
}
