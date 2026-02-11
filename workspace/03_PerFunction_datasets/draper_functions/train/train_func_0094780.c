tm_lookup_col_id(GtkTreeViewColumn *column) {
    gint i;

    if (column) {
        for (i = 0; i < TM_NUM_COLUMNS; ++i) {
            if (column == tm_columns[i])
                return i;
        }
    }
    return -1;
}
