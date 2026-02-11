spl_action_changed(GtkComboBox *combobox, GtkWidget *spl_window) {
    Playlist *spl;
    Itdb_SPLRule *splr;
    ItdbSPLFieldType ft;
    const ComboEntry *centries;
    gint index = gtk_combo_box_get_active(combobox);

    g_return_if_fail (index != -1);
    g_return_if_fail (spl_window);
    spl = g_object_get_data(G_OBJECT (spl_window), "spl_work");
    g_return_if_fail (spl);

    splr = g_object_get_data(G_OBJECT (combobox), "spl_rule");
    g_return_if_fail (splr);

    centries = g_object_get_data(G_OBJECT (combobox), "spl_centries");
    g_return_if_fail (centries);

    ft = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (combobox), "spl_fieldtype"));


    switch (ft) {
    case ITDB_SPLFT_BINARY_AND:
        if (splr->field == ITDB_SPLFIELD_VIDEO_KIND) {
            gint oldindex = GPOINTER_TO_INT (
                    g_object_get_data (G_OBJECT (combobox), "spl_binary_and_index"));
            if (oldindex != index) {

                splr->fromvalue = (~splr->fromvalue) & (0x0e00 | ITDB_MEDIATYPE_MOVIE | ITDB_MEDIATYPE_MUSICVIDEO
                        | ITDB_MEDIATYPE_TVSHOW);
                spl_update_rule(spl_window, splr);
            }
        }
        else {
            if (splr->action != centries[index].id) {
                splr->action = centries[index].id;

                spl_update_rule(spl_window, splr);
            }
        }
        break;
    default:
        if (splr->action != centries[index].id) {
            splr->action = centries[index].id;

            spl_update_rule(spl_window, splr);
        }
        break;
    }

}
