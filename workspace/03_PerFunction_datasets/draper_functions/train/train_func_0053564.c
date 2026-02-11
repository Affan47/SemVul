set_roms_liststore(int idx, const char *rom_key, SystemROM *rom) {
    ProfileValue *profile_value = get_current_profile_value(rom_key);
    const char *profile_rom_filename = (profile_value == NULL) ? NULL : profile_value->get_string_value();

    GtkListStore *store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(_w.roms_comboboxentry[idx])));
    gtk_list_store_clear(store);

    int active = -1;
    int list_entry = 0;
    ROMEntry *active_entry = NULL;
    const rom_entry_list_t roms = rom->get_roms();
    for (rom_entry_list_t::const_iterator it2 = roms.begin();it2 != roms.end();it2++) {
        ROMEntry *entry = (*it2);
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ROMS_DESCRIPTION_COLUMN, entry->get_description().c_str(),
                           ROMS_FILENAME_COLUMN, entry->get_filename().c_str(),
                           ROMS_TYPE_COLUMN, 1,
                           -1);

        if ((profile_rom_filename != NULL) && (entry->get_filename().compare(profile_rom_filename) == 0)) {
            active = list_entry;
            active_entry = entry;
        }
        list_entry++;
    }

    if ((active < 0) && (profile_rom_filename != NULL)) {
        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ROMS_DESCRIPTION_COLUMN, sys_basename(profile_rom_filename),
                           ROMS_FILENAME_COLUMN, profile_rom_filename,
                           ROMS_TYPE_COLUMN, 2,
                           -1);
        active = list_entry;
    }

    if (active < 0) {
        active = 0;
        active_entry = *roms.begin();

        int idx = 0;
        for (rom_entry_list_t::const_iterator it = roms.begin();it != roms.end();it++) {
            ROMEntry *entry = (*it);
            if (entry->is_default()) {
                active = idx;
                active_entry = entry;
                break;
            }
            idx++;
        }
    }

    char tooltip[128];
    snprintf(tooltip, sizeof(tooltip), _("ROM image is '%s'. The ROM size needs to be %04xh (%d) bytes."),
             active_entry != NULL ? active_entry->get_filename().c_str() : profile_rom_filename,
             rom->get_size(),
             rom->get_size());
    gtk_widget_set_tooltip_text(GTK_WIDGET(_w.roms_comboboxentry[idx]), tooltip);

    g_signal_handler_block(_w.roms_comboboxentry[idx], _w.on_rom_changed_id[idx]);
    gtk_combo_box_set_model(GTK_COMBO_BOX(_w.roms_comboboxentry[idx]), GTK_TREE_MODEL(store));
    gtk_combo_box_set_active(GTK_COMBO_BOX(_w.roms_comboboxentry[idx]), active);
    g_signal_handler_unblock(_w.roms_comboboxentry[idx], _w.on_rom_changed_id[idx]);
}
