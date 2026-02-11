sys_set_audio_state(int onoff)
{
    if (onoff)
    {
        if (!audio_isopen())
            sys_reopen_audio();
    }
    else
    {
        if (audio_isopen())
            sys_close_audio();
    }
}
