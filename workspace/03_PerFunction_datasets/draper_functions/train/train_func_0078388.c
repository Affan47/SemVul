qif_object_init(void)
{
    int i;
    static struct
    {
        QifType		type;
        struct _QifHandler	handler;
    } handlers[] =
    {
        { QIF_TYPE_BANK, { qif_txn_init, qif_txn_parse, qif_txn_end_acct } },
        { QIF_TYPE_CASH, { qif_txn_init, qif_txn_parse, qif_txn_end_acct } },
        { QIF_TYPE_CCARD, { qif_txn_init, qif_txn_parse, qif_txn_end_acct } },
        { QIF_TYPE_INVST, { qif_txn_init, qif_txn_invst_parse, qif_txn_end_acct } },
        { QIF_TYPE_PORT, { qif_txn_init, qif_txn_invst_parse, qif_txn_end_acct } },
        { QIF_TYPE_OTH_A, { qif_txn_init, qif_txn_parse, qif_txn_end_acct } },
        { QIF_TYPE_OTH_L, { qif_txn_init, qif_txn_parse, qif_txn_end_acct } },
        { QIF_TYPE_CLASS, { NULL, qif_class_parse, NULL } },
        { QIF_TYPE_CAT, { NULL, qif_cat_parse, NULL } },
        { QIF_TYPE_SECURITY, { NULL, qif_security_parse, NULL } },
        { QIF_ACCOUNT, { NULL, qif_account_parse, NULL } },
        { QIF_AUTOSWITCH, { qif_autoswitch_set, NULL, NULL } },
        { QIF_CLEAR_AUTOSWITCH, { qif_autoswitch_clear, NULL, NULL } },
        { 0, {NULL, NULL, NULL} }
    };

    for (i = 0; handlers[i].type > 0; i++)
    {
        if (handlers[i].type <= 0)
        {
            PERR("Invalid type?!?  (%d @ %d)", handlers[i].type, i);
        }
        else
            qif_register_handler(handlers[i].type, &(handlers[i].handler));
    }
}
