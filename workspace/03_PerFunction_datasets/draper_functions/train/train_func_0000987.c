comboentry_index_from_id(const ComboEntry centries[], guint32 id) {
    gint i;

    g_return_val_if_fail (centries, -1);


    if (centries == splaction_notsupported_comboentries)
        return 0;

    for (i = 0; centries[i].str; ++i) {
        if (centries[i].id == id)
            return i;
    }
    return -1;
}
