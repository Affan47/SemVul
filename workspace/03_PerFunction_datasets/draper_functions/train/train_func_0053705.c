gnc_split_register_save_memo_cell (BasicCell * cell,
                                   gpointer save_data,
                                   gpointer user_data)
{
    SRSaveData *sd = save_data;
    const char *value;

    g_return_if_fail (gnc_basic_cell_has_name (cell, MEMO_CELL));

    value = gnc_basic_cell_get_value (cell);

    DEBUG ("MEMO: %s", value ? value : "(null)");

    xaccSplitSetMemo (sd->split, value);
}
