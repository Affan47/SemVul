BuildWindow(void)
{
    char buf[50];
    txt_table_t *table;
    int i;

    TXT_ClearTable(window);
    table = TXT_NewTable(3);
    TXT_AddWidget(window, table);


    TXT_AddWidget(table, NULL);
    TXT_AddWidget(table, TXT_NewStrut(25, 1));
    TXT_AddWidget(table, TXT_NewStrut(17, 1));


    for (i = 0; i < net_client_wait_data.max_players; ++i)
    {
        sprintf(buf, " %i. ", i + 1);
        TXT_AddWidget(table, TXT_NewLabel(buf));
        player_labels[i] = TXT_NewLabel("");
        ip_labels[i] = TXT_NewLabel("");
        TXT_AddWidget(table, player_labels[i]);
        TXT_AddWidget(table, ip_labels[i]);
    }

    drone_label = TXT_NewLabel("");

    TXT_AddWidget(window, drone_label);
}
