gnc_tree_model_split_reg_get_read_only (GncTreeModelSplitReg *model, Transaction *trans)
{
    if (qof_book_is_readonly (model->priv->book))
        return TRUE;

    if (model->read_only)
        return TRUE;


    if (xaccTransHasSplitsInState (trans, VREC))
        return TRUE;

    if (qof_book_uses_autoreadonly (model->priv->book))
    {
        if (trans == model->priv->btrans)
            return FALSE;
        else
            return xaccTransIsReadonlyByPostedDate (trans);
    }
    return FALSE;
}
