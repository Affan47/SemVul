gnc_account_child_index (const Account *parent, const Account *child)
{
    g_return_val_if_fail(GNC_IS_ACCOUNT(parent), -1);
    g_return_val_if_fail(GNC_IS_ACCOUNT(child), -1);
    return g_list_index(GET_PRIVATE(parent)->children, child);
}
