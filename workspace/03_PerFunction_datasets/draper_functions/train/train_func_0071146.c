validate_item_pass2(gpointer hash_key,
                    G_GNUC_UNUSED gpointer hash_value,
                    gpointer user_data)
{
    GQuark key = GPOINTER_TO_UINT(hash_key);
    GwyDataValidationInfo *info = (GwyDataValidationInfo*)user_data;
    GSList **errors;
    const gchar *strkey;
    gint id;
    guint len;
    GwyAppKeyType type;

    errors = &info->errors;
    strkey = g_quark_to_string(key);
    id = _gwy_app_analyse_data_key(strkey, &type, &len);
    if (id < 0 || id >= (1 << 20))
        return;


    switch (type) {
        case KEY_IS_MASK:
        case KEY_IS_SHOW:
        case KEY_IS_CHANNEL_META:
        case KEY_IS_TITLE:
        case KEY_IS_PALETTE:
        case KEY_IS_3D_PALETTE:
        case KEY_IS_3D_MATERIAL:
        case KEY_IS_SELECT:
        case KEY_IS_RANGE_TYPE:
        case KEY_IS_SPS_REF:
        case KEY_IS_RANGE:
        case KEY_IS_MASK_COLOR:
        case KEY_IS_REAL_SQUARE:
        case KEY_IS_DATA_VISIBLE:
        case KEY_IS_3D_SETUP:
        case KEY_IS_3D_LABEL:
        if (!in_array(info->channels, id))
            *errors = g_slist_prepend(*errors,
                                      FAIL(GWY_DATA_ERROR_STRAY_SECONDARY_DATA,
                                           key,
                                           _("no channel %d exists for %s"),
                                           id, strkey));
        break;

        case KEY_IS_GRAPH_VISIBLE:
        if (!in_array(info->graphs, id))
            *errors = g_slist_prepend(*errors,
                                      FAIL(GWY_DATA_ERROR_STRAY_SECONDARY_DATA,
                                           key,
                                           _("no graph %d exists for %s"),
                                           id, strkey));
        break;

        case KEY_IS_SPECTRA_VISIBLE:
        if (!in_array(info->spectra, id))
            *errors = g_slist_prepend(*errors,
                                      FAIL(GWY_DATA_ERROR_STRAY_SECONDARY_DATA,
                                           key,
                                           _("no spectra %d exists for %s"),
                                           id, strkey));
        break;

        case KEY_IS_BRICK_VISIBLE:
        case KEY_IS_BRICK_TITLE:
        case KEY_IS_BRICK_PREVIEW:
        case KEY_IS_BRICK_PREVIEW_PALETTE:
        case KEY_IS_BRICK_META:
        if (!in_array(info->volumes, id))
            *errors = g_slist_prepend(*errors,
                                      FAIL(GWY_DATA_ERROR_STRAY_SECONDARY_DATA,
                                           key,
                                           _("no brick %d exists for %s"),
                                           id, strkey));

        default:
        break;
    }
}
