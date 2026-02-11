create_preset_from_data(GList *list)
{
    GString *data;
    GList *iter;
    gint total, n, x;
    gint bank, number, modified;
    gchar *name;

    g_return_val_if_fail(list != NULL, NULL);

    Preset *preset = g_slice_new(Preset);
    preset->name = NULL;
    preset->params = NULL;
    preset->genetxs = NULL;

    iter = list;
    for (iter = list; iter; iter = g_list_next(iter)) {
        data = (GString*) iter->data;
        switch (get_message_id(data)) {
            case RECEIVE_PRESET_START:
                bank = (unsigned char)data->str[8];
                number = (unsigned char)data->str[9];
                name = g_strdup(&data->str[10]);
                modified = (unsigned char)data->str[11+strlen(name)];

                if ((bank == PRESETS_EDIT_BUFFER) && (number == 0)) {
                    debug_msg(DEBUG_MSG2HOST,
                              "RECEIVE_PRESET_START:  current edit buffer");
                } else {
                    debug_msg(DEBUG_MSG2HOST,
                              "RECEIVE_PRESET_START: preset %d from bank %d",
                              number, bank);
                }

                debug_msg(DEBUG_MSG2HOST, "Name: %s, %sodified",
                                          name, modified ? "M" : "Not m");
                preset->name = name;
                break;
            case RECEIVE_PRESET_PARAMETERS:
                x = 0x09;
                n = 0;
                total = (unsigned char)data->str[x];
                x++;

                do {
                    SettingParam *param = setting_param_new_from_data(&data->str[x], &x);
                    n++;
                    preset->params = g_list_prepend(preset->params, param);
                    if (debug_flag_is_set(DEBUG_MSG2HOST)) {
                        GString *ipv = format_ipv(param->id, param->position, param->value);
                        debug_msg(DEBUG_MSG2HOST, "%3d %s", n, ipv->str);
                        g_string_free(ipv, TRUE);
                    }
                } while ((x < data->len) && n<total);
                debug_msg(DEBUG_MSG2HOST, "TOTAL %d", total);
                preset->params = g_list_sort(preset->params, params_cmp);
                break;
            case RECEIVE_PRESET_END:
                break;
            default:
                g_warning("Unhandled message 0x%x in preset messages list",
                          get_message_id(data));
        }
    }

    return preset;
}
