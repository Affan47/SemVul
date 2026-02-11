ShouldRestartCDTrack(void)
{
    return cd_track_end_time != 0 && I_GetTimeMS() > cd_track_end_time;
}
