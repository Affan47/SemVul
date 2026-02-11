gnc_tree_view_account_filter_by_view_info(Account* acct, gpointer data)
{
    GNCAccountType acct_type;
    AccountViewInfo* avi = (AccountViewInfo*)data;

    g_return_val_if_fail(GNC_IS_ACCOUNT(acct), FALSE);
    acct_type = xaccAccountGetType(acct);

    if (!avi->include_type[acct_type]) return FALSE;
    if (!avi->show_hidden && xaccAccountIsHidden(acct)) return FALSE;
    return TRUE;
}
