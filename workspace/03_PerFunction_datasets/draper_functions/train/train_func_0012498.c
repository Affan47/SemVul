update_account_list(ABInitialInfo *info)
{
    AB_ACCOUNT_LIST2 *acclist;

    g_return_if_fail(info && info->api && info->gnc_hash);


    g_object_ref(info->account_store);
    gtk_tree_view_set_model(info->account_view, NULL);


    gtk_list_store_clear(info->account_store);
    acclist = AB_Banking_GetAccounts(info->api);
    if (acclist)
        AB_Account_List2_ForEach(acclist, update_account_list_acc_cb, info);
    else
        g_warning("update_account_list: Oops, account list from AB_Banking "
                  "is NULL");


    gtk_tree_view_set_model(info->account_view,
                            GTK_TREE_MODEL(info->account_store));

    g_object_unref(info->account_store);
}
