instantiate_cashflow_internal(const SchedXaction* sx,
                              GHashTable* map,
                              GList **creation_errors, gint count)
{
    SxCashflowData create_cashflow_data;
    Account* sx_template_account = gnc_sx_get_template_transaction_account(sx);

    if (!sx_template_account)
    {
        g_critical("Huh? No template account for the SX %s", xaccSchedXactionGetName(sx));
        return;
    }

    if (!xaccSchedXactionGetEnabled(sx))
    {
        g_debug("Skipping non-enabled SX [%s]",
                xaccSchedXactionGetName(sx));
        return;
    }

    create_cashflow_data.hash = map;
    create_cashflow_data.creation_errors = creation_errors;
    create_cashflow_data.sx = sx;
    create_cashflow_data.count = gnc_numeric_create(count, 1);


    xaccAccountForEachTransaction(sx_template_account,
                                  create_cashflow_helper,
                                  &create_cashflow_data);
}
