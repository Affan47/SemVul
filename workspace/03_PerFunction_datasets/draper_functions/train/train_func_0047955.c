input_amiga_menu_function(fs_emu_menu_item *menu_item,
        void **result_data) {
    int port = fs_emu_menu_item_get_idata(menu_item);
    char *str;
    fs_emu_menu_item *item;
    fs_emu_menu *menu = fs_emu_menu_new();
    menu->idata = port;

    item = fs_emu_menu_item_new();
    fs_emu_menu_append_item(menu, item);

    str = fs_strdup_printf(_("Joystick Port %d Mode"), port);
    fs_emu_menu_item_set_title(item, str);
    free(str);
    fs_emu_menu_item_set_type(item, FS_EMU_MENU_ITEM_TYPE_HEADING);

    int index = 0;

    item = fs_emu_menu_item_new();
    index++;
    fs_emu_menu_append_item(menu, item);
    fs_emu_menu_item_set_title(item, NO_AMIGA_DEVICE);
    fs_emu_menu_item_set_idata(item, (port << 8) | 0);
    fs_emu_menu_item_set_activate_function(item, input_type_function);
    if (g_fs_uae_input_ports[port].mode == 0) {
        menu->index = index;
    }

    if (port < 2) {
        item = fs_emu_menu_item_new();
        index++;
        fs_emu_menu_append_item(menu, item);
        fs_emu_menu_item_set_title(item, _("Mouse Mode"));
        fs_emu_menu_item_set_idata(item, (port << 8) | AMIGA_JOYPORT_MOUSE);
        fs_emu_menu_item_set_activate_function(item, input_type_function);
        if (g_fs_uae_input_ports[port].mode == AMIGA_JOYPORT_MOUSE) {
            menu->index = index;
        }
    }

    if (port < 4) {
        item = fs_emu_menu_item_new();
        index++;
        fs_emu_menu_append_item(menu, item);
        fs_emu_menu_item_set_title(item, _("Joystick Mode"));
        fs_emu_menu_item_set_idata(item, (port << 8) | AMIGA_JOYPORT_DJOY);
        fs_emu_menu_item_set_activate_function(item, input_type_function);
        if (g_fs_uae_input_ports[port].mode == AMIGA_JOYPORT_DJOY) {
            menu->index = index;
        }
    }

    if (port < 2) {
        item = fs_emu_menu_item_new();
        index++;
        fs_emu_menu_append_item(menu, item);
        fs_emu_menu_item_set_title(item, _("CD32 Pad Mode"));
        fs_emu_menu_item_set_idata(item, (port << 8) | AMIGA_JOYPORT_CD32JOY);
        fs_emu_menu_item_set_activate_function(item, input_type_function);
        if (g_fs_uae_input_ports[port].mode == AMIGA_JOYPORT_CD32JOY) {
            menu->index = index;
        }
    }

    if (port >= 4) {
        item = fs_emu_menu_item_new();
        index++;
        fs_emu_menu_append_item(menu, item);
        fs_emu_menu_item_set_title(item, _("Custom Mode"));
        fs_emu_menu_item_set_idata(item, (port << 8) | AMIGA_JOYPORT_DJOY);
        fs_emu_menu_item_set_activate_function(item, input_type_function);
        if (g_fs_uae_input_ports[port].mode == AMIGA_JOYPORT_DJOY) {
            menu->index = index;
        }
    }

    *result_data = menu;
    return FS_EMU_MENU_RESULT_MENU;
}
