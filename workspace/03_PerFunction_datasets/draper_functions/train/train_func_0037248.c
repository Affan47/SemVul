I_CDMusLastTrack(void)
{
    if (cd_handle == NULL)
    {
        cd_Error = 1;
        return -1;
    }

    cd_Error = 0;

    return cd_handle->numtracks;
}
