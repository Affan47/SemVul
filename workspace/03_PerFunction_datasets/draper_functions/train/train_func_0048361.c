gnc_ab_import_context(AB_IMEXPORTER_CONTEXT *context,
                      guint awaiting, gboolean execute_txns,
                      AB_BANKING *api, GtkWidget *parent)
{
    GncABImExContextImport *data = g_new(GncABImExContextImport, 1);

    g_return_val_if_fail(context, NULL);

    g_return_val_if_fail(!(awaiting & AWAIT_BALANCES)
                         || !(awaiting & IGNORE_BALANCES),
                         NULL);
    g_return_val_if_fail(!(awaiting & AWAIT_TRANSACTIONS)
                         || !(awaiting & IGNORE_TRANSACTIONS),
                         NULL);

    g_return_val_if_fail(awaiting & AWAIT_TRANSACTIONS || !execute_txns, NULL);

    g_return_val_if_fail(!execute_txns || api, NULL);

    data->awaiting = awaiting;
    data->txn_found = FALSE;
    data->execute_txns = execute_txns;
    data->api = api;
    data->parent = parent;
    data->job_list = AB_Job_List2_new();
    data->tmp_job_list = NULL;
    data->generic_importer = NULL;

    g_datalist_init(&data->tmp_job_list);


    if (!(awaiting & IGNORE_TRANSACTIONS))
        AB_ImExporterContext_AccountInfoForEach(context, txn_accountinfo_cb,
                                                data);


    if (!(awaiting & IGNORE_BALANCES))
        AB_ImExporterContext_AccountInfoForEach(context, bal_accountinfo_cb,
                                                data);

    return data;
}
