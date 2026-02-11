tip_blind_do_images(TipBlindControls *controls,
                    TipBlindArgs *args)
{
    gint newid, i;

    for (i = 0; i < args->nstripes; i++) {
        gchar *title;
        gchar key[24];

        if (!args->goodtip[i] || !args->stripetips[i])
            continue;

        newid = gwy_app_data_browser_add_data_field(args->stripetips[i],
                                                    args->source.data, TRUE);
        gwy_app_sync_data_items(args->source.data, args->source.data,
                                0, newid, FALSE,
                                GWY_DATA_ITEM_GRADIENT, 0);
        title = g_strdup_printf("%s %u/%u",
                                _("Estimated tip"), i+1, args->nstripes);
        g_snprintf(key, sizeof(key), "/%d/data/title", newid);
        gwy_container_set_string_by_name(args->source.data, key, title);
    }


    controls->tipdone = TRUE;
}
