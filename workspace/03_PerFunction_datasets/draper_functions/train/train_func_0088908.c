CheckExecutableName(GameSelectCallback callback)
{
    mission_config_t *config;
    char *exe_name;
    int i;

    exe_name = M_GetExecutableName();

    for (i=0; i<arrlen(mission_configs); ++i)
    {
        config = &mission_configs[i];

        if (strstr(exe_name, config->name) != NULL)
        {
            SetMission(config);
            callback();
            return true;
        }
    }

    return false;
}
