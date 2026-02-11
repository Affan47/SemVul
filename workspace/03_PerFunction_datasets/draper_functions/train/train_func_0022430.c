set_default_kbdui (void *window)
{
    const gchar *section = "engine/input-pad/default_table";
    const gchar *name = NULL;
    gchar *str = NULL;

    name = "keyboard_theme";
    ibus_input_pad_config_get_str (config, section, name, &str);

    if (str && g_strcmp0 (str, "default") != 0) {
        input_pad_window_set_kbdui_name (window, str);
    } else {
        input_pad_window_set_kbdui_name (window, NULL);
    }
    g_free (str);
}
