update_cd_menu(fs_emu_menu *menu) {
    fs_emu_menu_item *item = menu->items[1];
    const char *inserted_path = amiga_cdrom_get_file(menu->idata);


    for (int i = 0; i < menu->count - 2; i++) {
        item = menu->items[i + 2];
        char *key = fs_strdup_printf("cdrom_image_%d", i);
        char* path = fs_config_get_string(key);
        free(key);
        if (path == NULL) {
            fs_emu_menu_item_set_enabled(item, 0);
            continue;
        }
        if (strcmp(inserted_path, path) == 0) {
            fs_emu_menu_item_set_enabled(item, 0);

            menu->index = 2 + i;
        }
        else {
            fs_emu_menu_item_set_enabled(item, 1);
        }
        free(path);
    }
}
