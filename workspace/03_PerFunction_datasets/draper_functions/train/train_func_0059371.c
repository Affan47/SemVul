fs_uae_read_override_actions_for_port(int port) {
    fs_log("fs_uae_read_override_actions_for_port %d\n", port);
    fs_emu_input_mapping *mapping = g_joystick_mappings[port];
    for (int i = 0; i < FS_UAE_MAX_PORT_ACTIONS; i++) {
        if (mapping[i].name == NULL) {
            continue;
        }
        const char* name = mapping[i].name;
        if (strcmp(name, "1") == 0) {
            name = "primary";
        }
        else if (strcmp(name, "2") == 0) {
            name = "secondary";
        }
        char *key = fs_strdup_printf("joystick_port_%d_%s", port, name);
        const char *value = fs_config_get_const_string(key);
        if (value == NULL) {
            continue;
        }
        fs_log("check %s = %s\n", key, value);
        int action = fs_emu_input_action_from_string(value);
        if (action > -1) {
            fs_log("override %s => %s (%d)\n", key, value, action);
            mapping[i].action = action;
        }
        free(key);
    }
}
