fs_uae_configure_amiga_model() {
    char *path;

    fs_emu_log("fs_uae_configure_amiga_model\n");
    fs_uae_init_configs();


    if (fs_config_get_boolean("ntsc_mode") == 1) {
        fs_emu_log("enabling NTSC mode (60Hz)\n");
        g_fs_uae_ntsc_mode = 1;
        fs_emu_set_video_frame_rate(60);
    }
    else {
        fs_emu_log("using PAL mode (50Hz)\n");
        fs_emu_set_video_frame_rate(50);
    }

    g_fs_uae_amiga_config = -1;

    const char *config_model = fs_config_get_const_string("amiga_model");
    if (config_model == NULL) {
        config_model = fs_config_get_const_string("model");
    }
    if (config_model) {
        int i = 0;
        for (amiga_config* c = g_fs_uae_amiga_configs; c->id; c++, i++) {
            if (fs_ascii_strcasecmp(config_model, c->id) == 0) {
                fs_emu_log("config match for \"%s\"\n", c->id);
                g_fs_uae_amiga_config = i;
                break;
            }

        }
    }
    if (g_fs_uae_amiga_config == -1) {
        fs_emu_log("WARNING: unknown amiga config specified, using A500\n");
        g_fs_uae_amiga_config = CONFIG_A500;
    }

    amiga_config *c = g_fs_uae_amiga_configs + g_fs_uae_amiga_config;
    g_fs_uae_amiga_model = c->model;
    g_accuracy = fs_config_get_int_clamped("accuracy", -2, 1);

    if (c->no_accuracy_adjustment) {
        fs_emu_log("ignoring accuracy for this model\n");
        g_accuracy = 1;
    }

    if (g_accuracy == FS_CONFIG_NONE) {
        g_accuracy = 1;
    }
    if (g_accuracy <= c->fast_on_accuracy_level) {
        fs_emu_log("this model / accuracy combination is a "
                "\"fastest possibly\" mode\n");
        g_fs_uae_fastest_possible = 1;
    }

    if (!fs_emu_get_title()) {
        fs_emu_set_title(c->name);
    }
    if (!fs_emu_get_sub_title()) {
        fs_emu_set_sub_title("FS-UAE");
    }
    if (c->warning) {
        fs_emu_warning(c->warning);
    }
}
