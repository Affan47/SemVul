I_InitTimidityConfig(void)
{
    char *env_string;
    boolean success;

    temp_timidity_cfg = M_TempFile("timidity.cfg");

    if (snd_musicdevice == SNDDEVICE_GUS)
    {
        success = GUS_WriteConfig(temp_timidity_cfg);
    }
    else
    {
        success = WriteWrapperTimidityConfig(temp_timidity_cfg);
    }


    if (success)
    {
        env_string = malloc(strlen(temp_timidity_cfg) + 15);
        sprintf(env_string, "TIMIDITY_CFG=%s", temp_timidity_cfg);
        putenv(env_string);
    }
    else
    {
        Z_Free(temp_timidity_cfg);
        temp_timidity_cfg = NULL;
    }
}
