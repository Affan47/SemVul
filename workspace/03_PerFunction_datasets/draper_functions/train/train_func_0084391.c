settings_gui_init(void)
{
    gint n;

    gui_prop_set_stub = gui_prop_get_stub();
    gnet_prop_set_stub = gnet_prop_get_stub();

    tooltips = gtk_tooltips_new();
    properties = gui_prop_init();
	sensitive_changes = hikset_create(
		offsetof(struct widget_change, name), HASH_KEY_STRING, 0);

   	prop_load_from_file(properties, settings_gui_config_dir(), property_file);

    for (n = 0; n < GUI_PROPERTY_NUM; n ++) {
        gui_init_list[n] = NOT_IN_MAP;
    }

    for (n = 0; n < GNET_PROPERTY_NUM; n ++) {
        gnet_init_list[n] = NOT_IN_MAP;
    }

    settings_gui_init_prop_map();


#ifndef USE_REMOTE_CTRL
	gtk_widget_set_sensitive(
		gui_dlg_prefs_lookup("checkbutton_enable_remote_shell"), FALSE);
#endif
}
