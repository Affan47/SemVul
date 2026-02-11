I_CDMusFirstTrack(void)
{
    int i;

    if (cd_handle == NULL)
    {
        cd_Error = 1;
        return -1;
    }


    for (i=0; i<cd_handle->numtracks; ++i)
    {
        if (cd_handle->track[i].type == SDL_AUDIO_TRACK)
        {
            cd_Error = 0;


            return i + 1;
        }
    }


    cd_Error = 1;

    return -1;
}
