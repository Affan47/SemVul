ds_get_config_dir()
{
    char *ds_name;
    char *configdir_env;
    static char configdir[PATH_MAX];

    if ((configdir_env = getenv("DS_CONFIG_DIR"))) {
        return configdir_env;
    } else {
        if ( (ds_name = ds_get_server_name()) == NULL )
            return(NULL);
        PR_snprintf(configdir, sizeof(configdir), "%s/%s", INSTCONFIGDIR, ds_name);
        return (configdir);
    }
}
