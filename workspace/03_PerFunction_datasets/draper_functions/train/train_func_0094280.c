vnc_display_keyval_free_entries(void)
{
    size_t i;

    if (ref_count_for_untranslated_keys == 0)
        return;

    ref_count_for_untranslated_keys--;
    if (ref_count_for_untranslated_keys == 0)
        for (i = 0; i < G_N_ELEMENTS(untranslated_keys); i++)
            g_free(untranslated_keys[i].keys);

}
