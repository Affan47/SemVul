lcrt_destroy_settings(struct lcrt_settings *lsettings)
{
    if (lsettings->auto_save_config)
        lcrt_settings_save_local_config(lsettings);

    if (lsettings)
        free(lsettings);
}
