osinfo_install_config_init (OsinfoInstallConfig *config)
{
    gchar pass[9];
    gsize i;

    config->priv = OSINFO_INSTALL_CONFIG_GET_PRIVATE(config);

    osinfo_entity_set_param(OSINFO_ENTITY(config),
                            OSINFO_INSTALL_CONFIG_PROP_L10N_KEYBOARD,
                            "en_US");
    osinfo_entity_set_param(OSINFO_ENTITY(config),
                            OSINFO_INSTALL_CONFIG_PROP_L10N_TIMEZONE,
                            "America/New_York");
    osinfo_entity_set_param(OSINFO_ENTITY(config),
                            OSINFO_INSTALL_CONFIG_PROP_L10N_LANGUAGE,
                            "en_US");

    for (i = 0 ; i < sizeof(pass)-1 ; i++) {
        gint val = g_random_int_range(0, sizeof(valid));
        pass[i] = valid[val];
    }
    pass[sizeof(pass)-1] = '\0';

    osinfo_entity_set_param(OSINFO_ENTITY(config),
                            OSINFO_INSTALL_CONFIG_PROP_ADMIN_PASSWORD,
                            pass);
}
