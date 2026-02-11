ibus_hangul_engine_hide_lookup_table (IBusHangulEngine *hangul)
{
    gboolean is_visible;
    is_visible = lookup_table_is_visible (hangul->table);


    if (is_visible) {
        ibus_engine_hide_lookup_table ((IBusEngine *)hangul);
        ibus_engine_hide_auxiliary_text ((IBusEngine *)hangul);
        lookup_table_set_visible (hangul->table, FALSE);
    }

    if (hangul->hanja_list != NULL) {
        hanja_list_delete (hangul->hanja_list);
        hangul->hanja_list = NULL;
    }
}
