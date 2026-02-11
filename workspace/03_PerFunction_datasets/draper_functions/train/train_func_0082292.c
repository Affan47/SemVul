gnc_tree_view_split_reg_reinit_trans (GncTreeViewSplitReg *view)
{
    Transaction           *trans;
    RowDepth               depth;


    gnc_tree_view_split_reg_finish_edit (view);

    trans = view->priv->current_trans;


    gnc_tree_control_split_reg_goto_rel_trans_row (view, 0);

    depth = view->priv->current_depth;

    if (trans && (depth != SPLIT3))
    {
        Split *s;
        int i = 0;

        if (!xaccTransIsOpen (trans))
            xaccTransBeginEdit (trans);

        gnc_tree_view_split_reg_set_dirty_trans (view, trans);

        while ((s = xaccTransGetSplit (trans, i)) != NULL)
        {
            if (xaccTransGetRateForCommodity (trans, view->priv->reg_comm, s, NULL))
                xaccSplitDestroy (s);
            else i++;
        }
    }
}
