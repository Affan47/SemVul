create_invoice_query (GncEntryLedger *ledger)
{
    QofQuery *q, *q1;
    char * type = NULL;

    if (!ledger->invoice)
        return;

    if (ledger->query)
        qof_query_destroy (ledger->query);


    ledger->query = qof_query_create_for (GNC_ENTRY_MODULE_NAME);
    qof_query_set_book (ledger->query, gncInvoiceGetBook (ledger->invoice));


    switch (ledger->type)
    {
    case GNCENTRY_INVOICE_ENTRY:
    case GNCENTRY_INVOICE_VIEWER:
    case GNCENTRY_CUST_CREDIT_NOTE_ENTRY:
    case GNCENTRY_CUST_CREDIT_NOTE_VIEWER:
        type = ENTRY_INVOICE;
        break;
    case GNCENTRY_BILL_ENTRY:
    case GNCENTRY_BILL_VIEWER:
    case GNCENTRY_EXPVOUCHER_ENTRY:
    case GNCENTRY_EXPVOUCHER_VIEWER:
    case GNCENTRY_VEND_CREDIT_NOTE_ENTRY:
    case GNCENTRY_VEND_CREDIT_NOTE_VIEWER:
    case GNCENTRY_EMPL_CREDIT_NOTE_ENTRY:
    case GNCENTRY_EMPL_CREDIT_NOTE_VIEWER:
        type = ENTRY_BILL;
        break;
    default:
        g_warning ("Invalid Ledger type");
        type = ENTRY_INVOICE;
        break;
    }

    q = qof_query_create_for (GNC_ENTRY_MODULE_NAME);
    qof_query_add_guid_match (q, qof_query_build_param_list (type, QOF_PARAM_GUID, NULL),
                              gncInvoiceGetGUID (ledger->invoice), QOF_QUERY_OR);


    if ((ledger->type == GNCENTRY_INVOICE_ENTRY ||
            ledger->type == GNCENTRY_CUST_CREDIT_NOTE_ENTRY) &&
            gncOwnerGetEndGUID (gncInvoiceGetOwner (ledger->invoice)) != NULL)
    {

        const GncGUID *invoice_parent =
            gncOwnerGetGUID (gncInvoiceGetOwner (ledger->invoice));
        QofQuery *q2 = qof_query_create_for (GNC_ENTRY_MODULE_NAME);


        qof_query_add_guid_match (q2, qof_query_build_param_list (ENTRY_BILLTO,
                                  QOF_PARAM_GUID, NULL),
                                  NULL, QOF_QUERY_AND);
        qof_query_add_guid_match (q2, qof_query_build_param_list (ENTRY_BILL, INVOICE_BILLTO,
                                  QOF_PARAM_GUID, NULL),
                                  invoice_parent, QOF_QUERY_AND);
        qof_query_add_guid_match (q2, qof_query_build_param_list (ENTRY_BILLTO,
                                  QOF_PARAM_GUID, NULL),
                                  invoice_parent, QOF_QUERY_OR);


        qof_query_add_boolean_match (q2, qof_query_build_param_list (ENTRY_BILLABLE, NULL),
                                     TRUE, QOF_QUERY_AND);
        qof_query_add_boolean_match (q2, qof_query_build_param_list (ENTRY_BILL,
                                     INVOICE_IS_POSTED, NULL),
                                     TRUE, QOF_QUERY_AND);


        qof_query_add_guid_match (q2, qof_query_build_param_list (ENTRY_ORDER, ORDER_OWNER,
                                  OWNER_PARENTG, NULL),
                                  invoice_parent, QOF_QUERY_OR);


        qof_query_add_guid_match (q2, qof_query_build_param_list (ENTRY_INVOICE,
                                  QOF_PARAM_GUID, NULL),
                                  NULL, QOF_QUERY_AND);


        q1 = qof_query_merge (q, q2, QOF_QUERY_OR);
        qof_query_destroy (q);
        qof_query_destroy (q2);
        q = q1;
    }


    q1 = qof_query_merge (ledger->query, q, QOF_QUERY_AND);
    qof_query_destroy (q);
    qof_query_destroy (ledger->query);
    ledger->query = q1;
}
