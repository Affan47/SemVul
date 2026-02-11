gnc_ab_accinfo_to_gnc_acc(AB_IMEXPORTER_ACCOUNTINFO *acc_info)
{
    const gchar *bankcode, *accountnumber;
    gchar *online_id;
    Account *gnc_acc;

    g_return_val_if_fail(acc_info, NULL);

    bankcode = AB_ImExporterAccountInfo_GetBankCode(acc_info);
    accountnumber = AB_ImExporterAccountInfo_GetAccountNumber(acc_info);
    online_id = g_strconcat(bankcode ? bankcode : "",
                            accountnumber ? accountnumber : "",
                            (gchar*)NULL);
    gnc_acc = gnc_import_select_account(
                  NULL, online_id, 1, AB_ImExporterAccountInfo_GetAccountName(acc_info),
                  NULL, ACCT_TYPE_NONE, NULL, NULL);
    if (!gnc_acc)
    {
        g_warning("gnc_ab_accinfo_to_gnc_acc: Could not determine source account"
                  " for online_id %s", online_id);
    }
    g_free(online_id);

    return gnc_acc;
}
