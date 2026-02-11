S_StartSong(int song, boolean loop)
{
    char *songLump;
    int lumpnum;
    int length;
    int track;


    if (cdmusic)
    {

        if (cd_custom_track != 0)
        {
            track = cd_custom_track;
        }
        else
        {
            track = P_GetMapCDTrack(gamemap);
        }

        StartCDTrack(track, loop);
    }
    else
    {
        if (song == Mus_Song)
        {
            return;
        }
        if (RegisteredSong)
        {
            I_StopSong();
            I_UnRegisterSong(RegisteredSong);
            RegisteredSong = 0;
        }
        songLump = P_GetMapSongLump(song);
        if (!songLump)
        {
            return;
        }

        lumpnum = W_GetNumForName(songLump);
        Mus_SndPtr = W_CacheLumpNum(lumpnum, PU_STATIC);
        length = W_LumpLength(lumpnum);

        RegisteredSong = I_RegisterSong(Mus_SndPtr, length);
        I_PlaySong(RegisteredSong, loop);
        Mus_Song = song;

        W_ReleaseLumpNum(lumpnum);
    }
}
