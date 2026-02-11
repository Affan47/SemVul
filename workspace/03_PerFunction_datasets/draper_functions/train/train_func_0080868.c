load_xfer_type_cells (GncEntryLedger *ledger)
{
    Account *root;
    ComboCell *cell;
    QuickFill *qf = NULL;
    GtkListStore *store = NULL;

    root = gnc_book_get_root_account (ledger->book);
    if (root == NULL) return;


    switch (ledger->type)
    {
    case GNCENTRY_ORDER_ENTRY:
    case GNCENTRY_ORDER_VIEWER:
    case GNCENTRY_INVOICE_ENTRY:
    case GNCENTRY_INVOICE_VIEWER:
    case GNCENTRY_CUST_CREDIT_NOTE_ENTRY:
    case GNCENTRY_CUST_CREDIT_NOTE_VIEWER:
        qf = gnc_get_shared_account_name_quickfill (root, IKEY,
                skip_expense_acct_cb, NULL);
        store = gnc_get_shared_account_name_list_store (root, IKEY,
                skip_expense_acct_cb, NULL);
        break;

    case GNCENTRY_BILL_ENTRY:
    case GNCENTRY_BILL_VIEWER:
    case GNCENTRY_EXPVOUCHER_ENTRY:
    case GNCENTRY_EXPVOUCHER_VIEWER:
    case GNCENTRY_VEND_CREDIT_NOTE_ENTRY:
    case GNCENTRY_VEND_CREDIT_NOTE_VIEWER:
    case GNCENTRY_EMPL_CREDIT_NOTE_ENTRY:
    case GNCENTRY_EMPL_CREDIT_NOTE_VIEWER:
    case GNCENTRY_NUM_REGISTER_TYPES:
        qf = gnc_get_shared_account_name_quickfill (root, EKEY,
                skip_income_acct_cb, NULL);
        store = gnc_get_shared_account_name_list_store (root, EKEY,
                skip_income_acct_cb, NULL);
        break;
    default:
	PWARN ("Bad GncEntryLedgerType");
	break;
    }

    cell = (ComboCell *)
           gnc_table_layout_get_cell (ledger->table->layout, ENTRY_IACCT_CELL);
    gnc_combo_cell_use_quickfill_cache (cell, qf);
    gnc_combo_cell_use_list_store_cache (cell, store);

    cell = (ComboCell *)
           gnc_table_layout_get_cell (ledger->table->layout, ENTRY_BACCT_CELL);
    gnc_combo_cell_use_quickfill_cache (cell, qf);
    gnc_combo_cell_use_list_store_cache (cell, store);
}
