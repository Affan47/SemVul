add_open_photo_editor(GtkWidget *menu) {
    iTunesDB *itdb = gtkpod_get_current_itdb();
    if (!itdb)
        return menu;

    if (! itdb_device_supports_photo(itdb->device))
        return menu;

    if (!gtkpod_has_photo_editor())
        return menu;

    return hookup_menu_item(menu, _("Open Photo Editor"), GTK_STOCK_SELECT_COLOR, G_CALLBACK (open_photo_editor), NULL);
}
