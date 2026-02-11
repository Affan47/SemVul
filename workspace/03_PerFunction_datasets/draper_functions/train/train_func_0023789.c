QueryPeriodicCallback(TXT_UNCAST_ARG(results_table))
{
    TXT_CAST_ARG(txt_table_t, results_table);

    if (!NET_Query_Poll(QueryResponseCallback, results_table))
    {
        TXT_SetPeriodicCallback(NULL, NULL, 0);

        if (query_servers_found == 0)
        {
            TXT_AddWidget(results_table, NULL);
            TXT_AddWidget(results_table, TXT_NewLabel("No servers found."));
        }
    }
}
